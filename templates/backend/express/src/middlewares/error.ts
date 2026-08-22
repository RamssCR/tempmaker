import type { ErrorRequestHandler } from 'express'
import { logger } from "#utils/logger";
import { parseError } from '#utils/parseError'

export const errorHandler: ErrorRequestHandler = (err, _req, res, _next) => {
    const { statusCode, message, details } = parseError(err)
    logger.error(details)

    res.status(statusCode).json({
        success: false,
        code: statusCode,
        message,
    })
}
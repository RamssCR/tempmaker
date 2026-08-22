import type { RequestHandler } from 'express'
import status from 'http-status'

export const errorPath: RequestHandler = (req, res) => {
    res.status(status.NOT_FOUND).json({
        status: status.NOT_FOUND,
        message: `Route ${req.originalUrl} not found`,
    })
}
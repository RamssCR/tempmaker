import { ZodError } from 'zod'
import { logger } from '#utils/logger'
import status from 'http-status'

export const parseError = (
    err: unknown,
): {
    statusCode: number
    message: string
    details: Record<string, unknown>
} => {
    if (err instanceof ZodError) {
        logger.error('Validation error', err)
        return {
            statusCode: status.BAD_REQUEST,
            message: 'Validation Error',
            details: {
                errors: err.issues.map(
                    (issue) => `${issue.path.join('.')} - ${issue.message}`,
                ),
            },
        }
    }

    if (err instanceof Error) {
        logger.error('Unexpected error', err)
        return {
            statusCode: status.INTERNAL_SERVER_ERROR,
            message: err.message,
            details: { name: err.name },
        }
    }

    logger.error('Unexpected non-error throwable', err)
    return {
        statusCode: status.INTERNAL_SERVER_ERROR,
        message: 'Internal Server Error',
        details: err as Record<string, unknown>,
    }
}
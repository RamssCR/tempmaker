import type { Request, RequestHandler } from 'express'
import status from 'http-status'
import { z } from 'zod'

type Target = 'headers' | 'body' | 'params' | 'query'
type Mode = 'full' | 'partial'
type ZodParams = {
    object: Record<string, unknown>
    schema: z.ZodSchema
    mode: Mode
}
type SchemaValidator = {
    target: keyof Pick<Request, Target>
    mode: Mode
}

const parseSchema = ({ object, schema, mode }: ZodParams) => {
    const parsed =
        mode === 'partial' && schema instanceof z.ZodObject
            ? schema.partial().safeParse(object)
            : schema.safeParse(object)
    return parsed.success
        ? parsed.data
        : parsed.error.issues.map(
            (issue) => `${issue.path.join('.')} - ${issue.message}`,
        )
}

export const validate = (schema: z.ZodSchema, { target = 'body', mode = 'full' }: Partial<SchemaValidator> = {}): RequestHandler =>
    async (req, res, next) => {
        try {
            const result = parseSchema({ object: req[target], schema, mode })

            if (Array.isArray(result) && result.length > 0)
                return res.status(status.BAD_REQUEST).json({
                    message: 'Error validating schema',
                    success: false,
                    details: result,
                })

            if (target === 'query') {
                Object.defineProperty(req, 'query', {
                    get: () => result,
                    enumerable: true,
                    configurable: true,
                })
            } else {
                req[target] = result
            }

            return next()
        } catch (error) {
            return next(error)
        }
    }
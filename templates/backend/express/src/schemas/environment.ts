import { z } from 'zod'

export const env = z.object({
    NODE_ENV: z
        .enum(['development', 'test', 'production', 'staging'])
        .default('development'),
    PORT: z.coerce.number().int().positive().default(3000),
    LIMIT: z.coerce.number().int().positive().default(30),
    LIMIT_MESSAGE: z
        .string()
        .default('Too many requests, please try again later'),
    ALLOWED_ORIGINS: z.string().transform((value) => value.trim().split(',')),
    DEBUG: z.preprocess((value) => {
        if (value === 'true') return true
        if (value === 'false') return false
        return value
    }, z.boolean().default(false)),
})

export type Env = z.infer<typeof env>
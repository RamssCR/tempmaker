import { LIMIT, LIMIT_MESSAGE } from '#config/environment'
import rateLimiter from 'express-rate-limit'

export const limiter = (skip = false) =>
    rateLimiter({
        skip: () => skip,
        windowMs: 30 * 1000,
        limit: LIMIT,
        message: LIMIT_MESSAGE,
        legacyHeaders: false,
    })
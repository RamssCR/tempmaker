import { env } from '#schemas/environment'
import { logger } from '#utils/logger'
import { treeifyError } from 'zod'

const parsed = env.safeParse(process.env)

if (!parsed.success) {
    logger.error(treeifyError(parsed.error)?.properties)
    process.exit(1)
}

export const {
    ALLOWED_ORIGINS,
    DEBUG,
    LIMIT,
    LIMIT_MESSAGE,
    NODE_ENV,
    PORT,
} = parsed.data
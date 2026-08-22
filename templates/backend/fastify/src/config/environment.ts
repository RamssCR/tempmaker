import { env } from '#schemas/environment'
import { treeifyError } from 'zod'

const parsed = env.safeParse(process.env)

if (!parsed.success) {
    console.error(treeifyError(parsed.error)?.properties)
    process.exit(1)
}

export const {
    ALLOWED_ORIGINS,
    LIMIT,
    NODE_ENV,
    PORT,
    THROTTLE_MB_PER_SECOND,
} = parsed.data
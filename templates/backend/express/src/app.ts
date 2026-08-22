import { ALLOWED_ORIGINS, NODE_ENV, PORT } from '#config/environment'
import express, { json, urlencoded } from 'express'
import { basename } from 'node:path'
import { cors } from '#middlewares/cors'
import { errorHandler } from '#middlewares/error'
import { errorPath } from '#middlewares/path'
import helmet from 'helmet'
import { limiter } from '#middlewares/limiter'
import { logger } from '#utils/logger'

const app = express()

app.use(json({ limit: '5mb' }))
app.use(urlencoded({ extended: true }))
app.use(helmet())

app.use(cors({ skip: NODE_ENV === 'development', origins: ALLOWED_ORIGINS }))
app.use(limiter(NODE_ENV === 'development'))

app.get('/health', (_, res) => {
    res.json({
        message: 'OK',
        date: new Date(),
        uptime: process.uptime(),
    })
})

app.use(errorPath)
app.use(errorHandler)

if (
    basename(import.meta.url) === basename(process.argv[1]) &&
    NODE_ENV !== 'test'
) {
    app.listen(PORT, () =>
        logger.info(`Servidor ejecutándose en http://localhost:${PORT}`),
    )
}
import {
    ALLOWED_ORIGINS,
    LIMIT,
    NODE_ENV,
    PORT,
    THROTTLE_MB_PER_SECOND,
} from '#config/environment'
import {
    type ZodTypeProvider,
    serializerCompiler,
    validatorCompiler,
} from 'fastify-type-provider-zod'
import Fastify from 'fastify'
import { basename } from 'node:path'
import cors from '@fastify/cors'
import helmet from '@fastify/helmet'
import limiter from '@fastify/rate-limit'
import throttle from '@fastify/throttle'

export const app = Fastify({ logger: true }).withTypeProvider<ZodTypeProvider>()

app.setValidatorCompiler(validatorCompiler)
app.setSerializerCompiler(serializerCompiler)

await app.register(throttle, {
    bytesPerSecond: THROTTLE_MB_PER_SECOND,
    streamPayloads: true,
    bufferPayloads: true,
    stringPayloads: true,
})

await app.register(cors, {
    origin: NODE_ENV === 'development' ? '*' : ALLOWED_ORIGINS,
    methods: ['GET', 'POST', 'PUT', 'DELETE'],
    allowedHeaders: ['Content-Type', 'Authorization'],
})

await app.register(helmet, { global: true })
await app.register(limiter, { max: LIMIT, timeWindow: 30 * 1000 })

app.get('/health', () => {
    return {
        status: 'OK',
        date: new Date(),
        uptime: process.uptime(),
    }
})

if (
    basename(import.meta.url) === basename(process.argv[1]) &&
    NODE_ENV !== 'test'
) {
    try {
        await app.listen({ port: PORT })
    } catch (error) {
        app.log.error(error)
        process.exit(1)
    }
}
import type { RequestHandler, Response } from 'express'
import type { Env } from '#schemas/environment'
import { NODE_ENV } from '#config/environment'
import httpStatus from 'http-status'

const DEFAULT_METHODS = ['GET', 'POST', 'PUT', 'DELETE'] as const
const DEFAULT_HEADERS = ['Content-Type', 'Authorization'] as const

type CorsOptions = {
    skip?: boolean
    origins?: string[]
    methods?: (typeof DEFAULT_METHODS)[number][]
    headers?: (typeof DEFAULT_HEADERS)[number][]
}

const parseHeader = (values: string[]) => values.join(', ')

const setCorsHeaders = (res: Response, origin: string, methods: string[], headers: string[]) => {
    res.header('Access-Control-Allow-Origin', origin)
    res.header('Access-Control-Allow-Methods', parseHeader(methods.map((value) => value.toUpperCase())))
    res.header('Access-Control-Allow-Headers', parseHeader(headers))
    res.header('Access-Control-Allow-Credentials', 'true')
}

const getAllowedOrigin = (requestOrigin: string, origins: string[], nodeEnv?: Env['NODE_ENV']) => {
    if (nodeEnv === 'development' || nodeEnv === 'test') return '*'
    return origins.includes(requestOrigin) ? requestOrigin : ''
}

export const cors = ({ skip = false, origins = [], methods = [...DEFAULT_METHODS], headers = [...DEFAULT_HEADERS]}: CorsOptions = {}): RequestHandler =>
    (req, res, next) => {
        if (skip) return next()

        const origin = req.headers?.origin
        if (!origin) return next()

        const allowedOrigin = getAllowedOrigin(origin, origins, NODE_ENV)
        setCorsHeaders(res, allowedOrigin, methods, headers)

        if (req.method === 'OPTIONS') return res.sendStatus(httpStatus.NO_CONTENT)
        return next()
    }
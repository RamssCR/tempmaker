import { config, createLogger, format, transports } from 'winston'
const { combine, errors, json, prettyPrint, timestamp } = format

export const logger = createLogger({
    levels: config.npm.levels,
    format: combine(json(), timestamp(), prettyPrint(), errors({ stack: true })),
    transports: [new transports.Console()],
})
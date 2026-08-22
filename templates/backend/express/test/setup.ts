import { afterEach, vi } from 'vitest'

afterEach(() => {
    vi.restoreAllMocks()
    vi.clearAllMocks()
    vi.resetModules()
    vi.useRealTimers()
})

vi.stubEnv('NODE_ENV', 'test')
vi.stubEnv('PORT', '3000')
vi.stubEnv('ALLOWED_ORIGINS', 'http://localhost:3000')
vi.stubEnv('DEBUG', 'false')
vi.stubEnv('LIMIT', '30')
vi.stubEnv('LIMIT_MESSAGE', 'Too many requests, please try again later')
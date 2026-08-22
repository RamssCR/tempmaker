import { afterEach, vi } from 'vitest'

afterEach(() => {
    vi.resetAllMocks()
    vi.restoreAllMocks()
    vi.resetModules()
    vi.useRealTimers()
    vi.unstubAllGlobals()
})

vi.stubEnv('NODE_ENV', 'test')

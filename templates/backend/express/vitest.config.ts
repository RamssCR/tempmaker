import { defineConfig, coverageConfigDefaults } from 'vitest/config'

export default defineConfig({
    resolve: { tsconfigPaths: true },
    test: {
        globals: true,
        environment: 'node',
        setupFiles: ['./test/setup.ts'],
        include: ['test/**/*.spec.{js,ts}'],
        reporters: process.env.GITHUB_ACTIONS ? ['github-actions'] : ['dot'],
        coverage: {
            provider: 'v8',
            reportsDirectory: 'coverage',
            reporter: ['json', 'json-summary', 'text'],
            thresholds: { statements: 90, branches: 90, functions: 90, lines: 90 },
            include: ['src/**/*.{js,ts}'],
            exclude: [
                '*.config.*',
                '**/index.ts',
                'src/app.ts',
                'src/routes/**',
                'src/config/**',
                ...coverageConfigDefaults.exclude,
            ],
        },
    },
})
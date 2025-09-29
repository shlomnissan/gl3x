import { defineConfig } from 'vitepress'
import referenceSidebar from './auto-reference-sidebar'

const year = new Date().getFullYear();

export default defineConfig({
  srcDir: 'pages',
  title: 'GL3X',
  description: '3D Rendering in Modern C++',
  cleanUrls: true,
  head: [
    ['link', { rel: 'preload', href: 'logo.woff2', as: 'font', type: 'font/woff2', crossorigin: '' }],
    ['link', { rel: 'icon', type: 'image/svg+xml', href: '/favicon.svg', media: '(prefers-color-scheme: light)' }],
    ['link', { rel: 'icon', type: 'image/svg+xml', href: '/favicon_white.svg', media: '(prefers-color-scheme: dark)' }],
    ['link', { rel: 'icon', href: '/favicon.ico', media: '(prefers-color-scheme: light)' }],
    ['link', { rel: 'icon', href: '/favicon_white.ico', media: '(prefers-color-scheme: dark)' }],
  ],
  themeConfig: {
    logo: {
      light: '/logo-light.svg',
      dark: '/logo-dark.svg'
    },
    nav: [
      { text: 'Guide', link: '/guide/', activeMatch: '^/guide/' },
      { text: 'Reference', link: '/reference/core/application', activeMatch: '^/reference/' }
    ],
    sidebar: {
      '/guide/': [
        {
          text: 'Get Started',
          items: [
            { text: 'Introduction', link: '/guide/' },
            { text: 'Installation', link: '/guide/installation' },
          ]
        }
      ],
      '/reference/': referenceSidebar,
    },
    footer: {
      message: 'Released under the MIT License.',
      copyright: `Copyright © 2024–${year}`
    },
    socialLinks: [
      { icon: 'github', link: 'https://github.com/shlomnissan/gleam' }
    ]
  }
})

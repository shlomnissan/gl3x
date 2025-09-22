import { defineConfig } from 'vitepress'
import referenceSidebar from './auto-reference-sidebar'

const year = new Date().getFullYear();

export default defineConfig({
  srcDir: 'pages',
  title: 'GL3X',
  description: '3D Rendering in Modern C++',
  cleanUrls: true,
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
      copyright: `Copyright © 2020–${year}`
    },
    socialLinks: [
      { icon: 'github', link: 'https://github.com/shlomnissan/gleam' }
    ]
  }
})

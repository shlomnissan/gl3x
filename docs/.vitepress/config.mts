import { defineConfig } from 'vitepress'

const year = new Date().getFullYear();

export default defineConfig({
  srcDir: 'pages',
  title: 'Gleam',
  description: '3D Rendering in Modern C++',
  head: [
    ['link', { rel: 'stylesheet', href: 'https://use.typekit.net/twl6gwz.css' }]
  ],
  themeConfig: {
    logo: {
      light: './logo-light.svg',
      dark: './logo-dark.svg'
    },
    nav: [
      { text: 'Home', link: '/' },
      { text: 'Examples', link: '/markdown-examples' }
    ],
    sidebar: [
      {
        text: 'Examples',
        items: [
          { text: 'Markdown Examples', link: '/markdown-examples' },
          { text: 'Runtime API Examples', link: '/api-examples' }
        ]
      }
    ],
    footer: {
      message: 'Released under the MIT License.',
      copyright: `Copyright © 2020–${year}`
    },
    socialLinks: [
      { icon: 'github', link: 'https://github.com/vuejs/vitepress' }
    ]
  }
})

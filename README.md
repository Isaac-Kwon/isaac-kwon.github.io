# isaac-kwon.github.io

Personal website of Minjae Isaac Kwon — <https://isaack.dev>

Built with Jekyll on GitHub Pages using the
[Minimal Mistakes](https://github.com/mmistakes/minimal-mistakes) theme as a
`remote_theme` (version pinned in `_config.yml`).

## Local preview

```bash
bundle install
bundle exec jekyll serve
```

## Site-specific overrides of the theme

- `assets/css/main.scss` — base font size override, imports `_sass/custom.scss`
- `_sass/custom/`, `_includes/expand` — collapsible `<details>` blocks
- `_layouts/custom/gplab.html` — GPLAB landing page layout

To update the theme, change the version in `remote_theme` and review the
upstream [CHANGELOG](https://github.com/mmistakes/minimal-mistakes/blob/master/CHANGELOG.md).

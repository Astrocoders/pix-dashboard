# PIX Dashboard

Saiba as empresas que estão na fila do PIX!

# Stack

- NFE.io API
- NextJS
- ReasonML

# Todo

- Nice stats
- Nice viz

## Data

Data comes from Banco Central do Brasil.

## Development

Run BuckleScript in dev mode:

```
npm run bs:start
```

In another tab, run the Next dev server:

```
npm run dev
```

## Useful commands

Build CSS seperately via `postcss` (useful for debugging)

```
# Devmode
postcss styles/main.css -o test.css

# Production
NODE_ENV=production postcss styles/main.css -o test.css
```

## Test production setup with Next

```
# Make sure to uncomment the `target` attribute in `now.json` first, before you run this:
npm run build
PORT=3001 npm start
```


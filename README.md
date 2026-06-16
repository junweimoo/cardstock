# cardstock

A static image composition engine — a C++ rendering core exposed as a Python
package, for composing text, vector shapes, and bitmaps into a single static
raster image. Aimed at social cards, server-rendered report pages, and
parameterized dynamic web graphics.

## Features

- **Canvas** — fixed-size RGBA surface; render to PNG bytes or save to disk.
- **Text** — arbitrary TTF/OTF fonts via FreeType + HarfBuzz shaping, behind a
  font registry that loads and caches faces by name.
- **Images** — decode bitmaps, scale with fit modes (`contain`/`cover`/`fill`),
  and apply rounded-corner masks; accepts raw RGBA buffers (e.g. a matplotlib
  figure) as first-class input.
- **Shapes** — rectangles with fill, stroke, and corner radius.
- **Placement** — absolute (`.at(x, y)`) or anchor + padding alignment
  (`.align("top-center", pad=64)`) against the canvas; nine named anchors.
- **Color** — hex (`"#0f172a"`, `"#fff"`), CSS names (`"white"`), or
  `(r, g, b[, a])` tuples; `"transparent"` is valid.
- **Deterministic & stateless** — identical inputs produce pixel-identical
  output across platforms

## Usage

The v1 product surface is a small declarative compositor — one canvas, three
element types, alignment helpers, and `render`/`save`:

```python
import cardstock as ie

ie.fonts.register("Inter-Bold", "fonts/Inter-Bold.ttf")
ie.fonts.register("Inter", "fonts/Inter-Regular.ttf")

card = (
    ie.Canvas(1200, 630, background="#0f172a")
      .add(ie.Rect(1200, 8, fill="#38bdf8").align("top-left"))
      .add(ie.Text("Weekly Report", font="Inter-Bold", size=64, color="white")
              .align("top-center", pad=64))
      .add(ie.Image("chart.png")
              .fit(box=(100, 180, 1000, 360), mode="contain"))
      .add(ie.Text("Generated June 2026", font="Inter", size=24, color="#94a3b8")
              .align("bottom-right", pad=40))
)

card.save("card.png")
# in a web handler:  return Response(card.render(), mimetype="image/png")
```

## Develop
```bash
uv venv && source .venv/bin/activate
uv pip install -e . --no-build-isolation
pytest
python examples/solid_card.py
```

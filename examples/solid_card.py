"""M0 demo: emit a solid-color PNG via the native core."""

import imgengine

img = imgengine.ImageBuffer(1200, 630)
img.fill(15, 23, 42, 255)
img.save_png("card.png")
print(f"wrote card.png ({img.width}x{img.height}) — imgengine {imgengine.__version__}")

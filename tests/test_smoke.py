import imgengine


def test_version():
    assert isinstance(imgengine.__version__, str)
    assert imgengine.__version__


def test_solid_png(tmp_path):
    img = imgengine.ImageBuffer(100, 100)
    img.fill(15, 23, 42, 255)  # slate-900
    out = tmp_path / "solid.png"
    img.save_png(str(out))

    assert out.exists()
    data = out.read_bytes()
    # PNG magic number
    assert data[:8] == b"\x89PNG\r\n\x1a\n"
    assert img.width == 100 and img.height == 100

# Eden's Manager

A small GTK 3 file-manager learning project written in C.

## Dependencies

On Debian/Ubuntu/Linux Mint:

```bash
sudo apt install build-essential pkg-config libgtk-3-dev adwaita-icon-theme librsvg2-bin
```

Toolbar icons use the system icon theme (symbolic names such as `go-previous-symbolic`). On Ubuntu, Yaru/Adwaita is usually enough; if icons are missing, install `yaru-theme-icon` or set `EDENS_DATA_DIR` when running from outside the project tree (must contain `edens.css`).

## Build

```bash
make
```

## Run

```bash
make run
```

Run from the **project root** so `data/edens.css` is found. On startup the terminal prints `edens: tema CSS ativo — fonte: ...`. If the window background turns **magenta**, the CSS file was not loaded or has a parse error (see the message above it in the terminal).

## Taskbar / dock icon (Ubuntu GNOME, etc.)

The window icon is embedded via GResource. Many desktops (especially Wayland) also need a `.desktop` entry and a themed icon name:

```bash
make install-launcher
```

Then start **Eden's Explorer** from the app menu, or log out/in so the shell picks up `~/.local/share/applications/com.edens.FileManager.desktop`.

If you only run `./edens` from the project folder, the dock may still show a generic icon until `install-launcher` is done.

## Clean

```bash
make clean
```

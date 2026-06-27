# Build pokeemerald ROM

## Prerequisites
- devkitpro installed at `/opt/devkitpro` via `devkitpro-pacman-installer.pkg`
- agbcc cloned and built at `../agbcc` (sibling of pokeemerald), installed into this repo
- `~/.zshrc` exports `DEVKITPRO=/opt/devkitpro` and `DEVKITARM=$DEVKITPRO/devkitARM`

## Build
```bash
make -j$(sysctl -n hw.ncpu)
```
If env vars aren't loaded in the current session, prefix with:
```bash
DEVKITPRO=/opt/devkitpro DEVKITARM=/opt/devkitpro/devkitARM make -j$(sysctl -n hw.ncpu)
```
Output: `pokeemerald.gba` (16 MB)

## Verify against original ROM
Requires `baserom.gba` (original Pokemon Emerald ROM) in the project root:
```bash
make compare
```

## First-time agbcc setup (if not already installed)
```bash
git clone https://github.com/pret/agbcc ../agbcc
cd ../agbcc
DEVKITPRO=/opt/devkitpro DEVKITARM=/opt/devkitpro/devkitARM ./build.sh
./install.sh ../pokeemerald
cd ../pokeemerald
```

## Reinstall devkitpro tools (if needed)
```bash
sudo dkp-pacman -Sy
sudo dkp-pacman -S gba-dev
sudo dkp-pacman -S devkitarm-rules
```

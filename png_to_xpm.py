from PIL import Image

# Function to reduce image to 93 colors or less
def reduce_image_colors(image, max_colors=93):
    return image.convert("P", palette=Image.ADAPTIVE, colors=max_colors)

# Function to convert the image to XPM format with one character per pixel
def convert_to_xpm(image_path, output_path):
    img = Image.open(image_path)
    img = reduce_image_colors(img)

    width, height = img.size
    pixels = img.load()

    # Define characters for XPM
    chars = ''.join(chr(i) for i in range(33, 126))
    if len(chars) < 93:
        raise ValueError("Not enough characters to map all colors")

    # Create a color map
    palette = img.getpalette()
    color_map = {}
    index = 0

    # Ensure the palette size is a multiple of 3
    palette = palette[:3 * 93]
    
    for i in range(0, len(palette), 3):
        color = (palette[i], palette[i + 1], palette[i + 2])
        color_map[index] = f'c #{color[0]:02x}{color[1]:02x}{color[2]:02x}'
        index += 1
        if index >= 93:
            break

    # Debugging output for color map
    print("Color Map:", color_map)

    # Write XPM file
    with open(output_path, 'w') as f:
        f.write("/* XPM */\nstatic char * image_xpm[] = {\n")
        f.write(f'"{width} {height} {len(color_map)} 1",\n')

        for i, color in color_map.items():
            f.write(f'"{chars[i]} {color}",\n')

        for y in range(height):
            row = ''.join(chars[pixels[x, y]] for x in range(width))
            f.write(f'"{row}",\n')
            # Debugging output for each row
            print(f"Row {y}: {row}")

        f.write("};\n")

    print(f"XPM file '{output_path}' created successfully with dimensions: {width}x{height}")

# Example usage
convert_to_xpm('sword5.png', 'output.xpm')

import os
from PIL import Image, ImageDraw, ImageFont, ImageChops

font = ImageFont.truetype("DejaVuSansMono.ttf", size=36)
output_folder = "./textures/numbers"

if not os.path.exists(output_folder):
    os.makedirs(output_folder)

for letter in '0123456789':
    img = Image.new('RGBA', (1, 1), color = (0, 0, 0, 0))
    d = ImageDraw.Draw(img)
    text_size = d.textsize(letter, font=font)
    img = Image.new('RGBA', text_size, color = (0, 0, 0, 0))
    d = ImageDraw.Draw(img)
    d.text((0, 0), letter, font=font, fill=(255, 255, 255))

    # Create a mask based on non-transparent pixels
    mask = ImageChops.difference(img, Image.new('RGBA', img.size, (0, 0, 0, 0)))
    mask = mask.convert('L').point(lambda i: i > 0 and 255)
    img.putalpha(mask)

    img.save(f'{output_folder}/{letter}.png', format='PNG')

    # Convert PNG to XPM using the 'convert' command
    os.system(f'convert {output_folder}/{letter}.png {output_folder}/{letter}.xpm')

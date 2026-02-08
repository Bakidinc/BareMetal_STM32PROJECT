import os

# Ayarlar
BOOTLOADER_SIZE = 0x8000  # 32KB
INPUT_FILE = "bootloader.bin"
OUTPUT_FILE = "bootloader_padded.bin"

def pad_file():
    if not os.path.exists(INPUT_FILE):
        print(f"Hata: {INPUT_FILE} bulunamadı!")
        return

    file_size = os.path.getsize(INPUT_FILE)
    
    if file_size > BOOTLOADER_SIZE:
        print(f"Hata: Bootloader boyutu ({file_size} byte) 32KB sınırını aşmış!")
        return

    with open(INPUT_FILE, "rb") as f:
        data = f.read()

    # Eksik kısmı 0xFF (Flash boş hali) ile doldur
    padding = b'\xff' * (BOOTLOADER_SIZE - file_size)
    
    with open(OUTPUT_FILE, "wb") as f:
        f.write(data + padding)
    
    print(f"Başarılı: {OUTPUT_FILE} oluşturuldu. Boyut: {os.path.getsize(OUTPUT_FILE)} byte.")

if __name__ == "__main__":
    pad_file()
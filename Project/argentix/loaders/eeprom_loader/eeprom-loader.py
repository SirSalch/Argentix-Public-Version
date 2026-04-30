import subprocess
import time
import os
import usb.core

VENDOR_ID = 0x16C0
PRODUCT_ID = 0x05DC

# Объявление директорий
script_dir = os.path.dirname(os.path.abspath(__file__))
jtag_dir = os.path.join(script_dir, "..", "..", "jtag")
firmware_dir = os.path.join(script_dir, "..", "..", "..", "build")


# Макросы записываемых ардесов в ОЗУ микроконтроллера
PROGRAMM_SIZE = "0x02000000" # Адрес хранения числа размера программы
LOADER_ADDR = "0x02000004" # Адрес начала загрузчика
APP_ADDR = "0x02000400" # Адрес начала загружаемого кода
SP_ADDR = "0x02004000" # Начало стека
PC_ADDR = LOADER_ADDR # Счетчик стекау


# Необходимые файлы для загрузки программы
config_link = os.path.join(jtag_dir, "mikron-link.cfg")
config_mcu = os.path.join(jtag_dir, "mik32.cfg")
firmware_bin= os.path.join(firmware_dir, "firmware.bin")
loader_bin = "eeprom-loader.bin"


# Размер программы и максимальная вместимость
firmware_size = os.path.getsize(loader_bin)
max_size = 8 * 1024 # 8 КБ


# Проверка на вметсимость в 8КБ ЕЕПРОМ памяти
if os.path.getsize(loader_bin) > max_size:
  print(f"[!Ошибка]: файл {loader_bin} превышает {max_size} байт")
  exit(1)


# Запуск JTAG
ocd_cmd = (
  f"init; halt;"
  f"load_image {loader_bin} {LOADER_ADDR} bin; "
  f"verify_image {loader_bin} {LOADER_ADDR} bin; "
  f"load_image {firmware_bin} {APP_ADDR} bin; "
  f"verify_image {firmware_bin} {APP_ADDR} bin; "
  f"reg pc {PC_ADDR};"
  f"reg sp {SP_ADDR};"
  f"mww {PROGRAMM_SIZE} {firmware_size}; "
  f"resume;"
  f"sleep 800;"
  f"halt;"
  f"reg sp {SP_ADDR};"
  f"reg pc 0x00000000;"
  f"resume;"
)

process = subprocess.Popen([
  "openocd",
  "-d0",
  "-f", config_link,
  "-f", config_mcu,
  "-c", ocd_cmd
])


try:
  while process.poll() is None:
    dev = usb.core.find(idVendor=VENDOR_ID, idProduct=PRODUCT_ID)
        
    if dev is None:
      process.terminate()
      process.wait()
      break
    
    time.sleep(1)

except KeyboardInterrupt:
  process.terminate()

exit()
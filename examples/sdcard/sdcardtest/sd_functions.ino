void setupSdCardShield()
{
  Serial.print("\nInitializing SD card...");
  pinMode(10, OUTPUT);     // change this to 53 on a mega
  //------------------------------------------------------------------------------
  checkShield();
  //------------------------------------------------------------------------------
  printCardType();
  //------------------------------------------------------------------------------
  openVolume(); // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  printVolumeDetails();
  //------------------------------------------------------------------------------
  root.openRoot(volume);
  listAllFiles();
  //------------------------------------------------------------------------------
}

void checkShield()
{
  if (!card.init(SPI_HALF_SPEED, chipSelect))
  {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card is inserted?");
    Serial.println("* Is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return;
  }
  else {
    Serial.println("Wiring is correct and a card is present.");
  }
}
//--------------------------------------------------------------------------------
void printCardType()
{
  Serial.print("\nCard type: ");
  switch (card.type())
  {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }
}

//--------------------------------------------------------------------------------
void openVolume()
{
  if (!volume.init(card))
  {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    while (!Serial) {}
  }
}
//--------------------------------------------------------------------------------

void printVolumeDetails()
{
  uint64_t volumesize64;
  uint32_t volumesize32;
  Serial.print("\nVolume type is FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println();

  volumesize64 = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize64 *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize64 *= 512;                         // SD card blocks are always 512 bytes

  Serial.print("Volume size (bytes): ");
  printLLNumber(volumesize64, DEC);
  Serial.println();

  Serial.print("Volume size (Kbytes): ");
  volumesize32 = volumesize64 / 1024;
  Serial.println(volumesize32);

  Serial.print("Volume size (Mbytes): ");
  volumesize32 /= 1024;
  Serial.println(volumesize32);
  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
}
//--------------------------------------------------------------------------------
void listAllFiles()
{
  root.ls(LS_R | LS_DATE | LS_SIZE);   // list all files in the card with date and size
}
//--------------------------------------------------------------------------------
void printLLNumber(uint64_t n, uint8_t base)
{
  unsigned char buf[16 * sizeof(long)];
  unsigned int i = 0;

  if (n == 0)
  {
    Serial.print((char)'0');
    return;
  }

  while (n > 0)
  {
    buf[i++] = n % base;
    n /= base;
  }

  for (; i > 0; i--)
    Serial.print((char) (buf[i - 1] < 10 ?
                         '0' + buf[i - 1] :
                         'A' + buf[i - 1] - 10));
}

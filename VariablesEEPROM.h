
#ifndef VARIABLES_EEPROM_H
#define VARIABLES_EEPROM_H


#include <vector>
#include <EEPROM.h>

class VariablesEEPROM {
  private:
    static VariablesEEPROM* instance;  // Instancia única de la clase
    static int MAX_PASSWORD_LENGTH;
    static int MAX_SSID_LENGTH;
    static int MAX_TOKEN_LENGTH;
    static int MAX_DEVICE_CODE_LENGTH;

    // Direcciones en la EEPROM para almacenar los campos
    static int PASSWORD_ADDRESS;
    static int SSID_ADDRESS;
    static int TOKEN_ADDRESS;
    static int DEVICE_CODE_ADDRESS;


    static std::vector<char> password;
    static std::vector<char> ssid;
    static std::vector<char> token;
    static std::vector<char> deviceCode;


    // Constructor privado para evitar instanciación directa
  private:
    VariablesEEPROM() {

    }

    static boolean guardarEnLaEEPROM(const char* value, int maxLength, int address, std::vector<char> container) {
      if (strlen(value) <= maxLength) {
        strcpy(container.data(), value);

        size_t containerLength = strlen(container.data());
        for (int i = 0; i < containerLength; i++) {
          EEPROM.write(address + i, container.data()[i]);
        }
        EEPROM.write(address + containerLength, '\0');  // Agregar el caracter nulo al final
        EEPROM.commit();
        return true;
      } else {
        return false;
      }
    }

    static String obtenerValorDeLaEEPROM(int maxLength, int address) {
      // Leer el valor de password de la EEPROM
      String value = "";
      for (int i = 0; i < maxLength; i++) {
        char c = char(EEPROM.read(address + i));
        if (c == '\0') {
          break;  // Se encontró el final de la cadena, se termina la lectura
        }
        value += c;
      }
      return value;
    }


  public:
    static boolean guardarPassword(const char* newPassword) {
      return VariablesEEPROM::guardarEnLaEEPROM(newPassword, VariablesEEPROM::MAX_PASSWORD_LENGTH, VariablesEEPROM::PASSWORD_ADDRESS, VariablesEEPROM::password);
    }

    static String obtenerPassword() {
      return VariablesEEPROM::obtenerValorDeLaEEPROM(VariablesEEPROM::MAX_PASSWORD_LENGTH, VariablesEEPROM::PASSWORD_ADDRESS);
    }

    static boolean guardarSSID(const char* newSSID) {
      return VariablesEEPROM::guardarEnLaEEPROM(newSSID, VariablesEEPROM::MAX_SSID_LENGTH, VariablesEEPROM::SSID_ADDRESS, VariablesEEPROM::ssid);
    }

    static String obtenerSSID() {
     return VariablesEEPROM::obtenerValorDeLaEEPROM(VariablesEEPROM::MAX_SSID_LENGTH, VariablesEEPROM::SSID_ADDRESS);
    }

    //este deberia ser eliminado una ves colocado el token
    static boolean guardarToken(const char* newToken) {
      return VariablesEEPROM::guardarEnLaEEPROM(newToken, VariablesEEPROM::MAX_TOKEN_LENGTH, VariablesEEPROM::TOKEN_ADDRESS, VariablesEEPROM::token);
    }

    static String obtenerToken() {
      return VariablesEEPROM::obtenerValorDeLaEEPROM(VariablesEEPROM::MAX_TOKEN_LENGTH, VariablesEEPROM::TOKEN_ADDRESS);
    }

    //este deberia ser eliminado una ves guardado el codigo
    static boolean guardarDeviceCode(const char* newDeviceCode) {
      return VariablesEEPROM::guardarEnLaEEPROM(newDeviceCode, VariablesEEPROM::MAX_DEVICE_CODE_LENGTH, VariablesEEPROM::DEVICE_CODE_ADDRESS, VariablesEEPROM::deviceCode);
    }

    static String obtenerDeviceCode() {
      return VariablesEEPROM::obtenerValorDeLaEEPROM(VariablesEEPROM::MAX_DEVICE_CODE_LENGTH, VariablesEEPROM::DEVICE_CODE_ADDRESS);
    }

    static int initSizeEEPROM() {
      return VariablesEEPROM::MAX_PASSWORD_LENGTH + VariablesEEPROM::MAX_SSID_LENGTH + VariablesEEPROM::MAX_TOKEN_LENGTH + VariablesEEPROM::MAX_DEVICE_CODE_LENGTH + 4;
    }

};



int VariablesEEPROM::MAX_PASSWORD_LENGTH = 100;
int VariablesEEPROM::MAX_SSID_LENGTH = 100;
int VariablesEEPROM::MAX_TOKEN_LENGTH = 100;
int VariablesEEPROM::MAX_DEVICE_CODE_LENGTH = 90;

int VariablesEEPROM::PASSWORD_ADDRESS = 0;
int VariablesEEPROM::SSID_ADDRESS = VariablesEEPROM::MAX_PASSWORD_LENGTH + 1;
int VariablesEEPROM::TOKEN_ADDRESS = VariablesEEPROM::SSID_ADDRESS + VariablesEEPROM::MAX_SSID_LENGTH + 1;
int VariablesEEPROM::DEVICE_CODE_ADDRESS = VariablesEEPROM::TOKEN_ADDRESS + VariablesEEPROM::MAX_TOKEN_LENGTH + 1;
VariablesEEPROM* VariablesEEPROM::instance = NULL;

std::vector<char> VariablesEEPROM::password(VariablesEEPROM::MAX_PASSWORD_LENGTH + 1);
std::vector<char> VariablesEEPROM::ssid(VariablesEEPROM::MAX_SSID_LENGTH + 1);
std::vector<char> VariablesEEPROM::token(VariablesEEPROM::MAX_TOKEN_LENGTH + 1);
std::vector<char> VariablesEEPROM::deviceCode(VariablesEEPROM::MAX_DEVICE_CODE_LENGTH + 1);

#endif

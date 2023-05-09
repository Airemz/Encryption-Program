#include <iostream>
#include <climits>

#ifndef MARMOSET_TESTING
int main();
#endif

// Will calculate the checksum if the number is 8 digits
// Input: n = 12345678 
// Output: 12345678d (d is check sum digit)
// Error: if n > 8 (9 digit number)
unsigned int add_checksum( unsigned int n ) {
  int checksum = 0;
  int temp = n;
  int temp2 = n;
  int number_of_digits = 0;
  int number_of_digits2 = 0;
  int digit_number = 0;
  int digits[8] ={0,0,0,0,0,0,0,0};
  
  if (n > 0 && n <= 99999999){
    
    //finding number of digits
    while (temp > 0){ 
      temp /= 10;
      number_of_digits += 1;
      number_of_digits2 +=1;
      }
    
    //adding digits to array backwards
    while (number_of_digits != 0){
      digits[digit_number] += temp2 % 10;

      digit_number++;
      temp2 /= 10;
      number_of_digits--;
      
    }
    
    //Checksum addition portion for every other number
    for (int i=0;i < 8;i+=2){
      if (digits[i] == 9){
        checksum+=9;
      }
      else if(digits[i] == 8){
        checksum+=7;
      }
      else if(digits[i] == 7){
        checksum+=5;
      }
      else if(digits[i] == 6){
        checksum+=3;
      }
      else if(digits[i] == 5){
        checksum+=1;
      }
      else{
        checksum += (digits[i] * 2);
      }

    }
    //addition for regular numbers  
    for (int i=1;i < 9;i+=2){
        checksum += digits[i];
    }
      
    
    checksum *= 9;
    checksum %= 10;

    n = n*10 + checksum;

    return n;
  }

  else{
    return UINT_MAX;
  }
  
  return 0;
}

void add_checksum( unsigned int array[], std::size_t capacity ){
  for (int a=0;a<capacity;a++){
    array[a] = add_checksum(array[a]);
  }
}

bool verify_checksum( unsigned int n ){
  int n2=n;
  n = n - (n % 10);
  n/=10;
  if (n < 999999999 && n2 % 10 == add_checksum(n) % 10){
    return true;
  }
  else {
    return false;
  }
  return 0;
}

unsigned int remove_checksum( unsigned int n ){
  if ((verify_checksum(n)==false) || n > 999999999){
    return UINT_MAX;
  }
  else{
    n = n - (n%10);
    n/=10;
    return n;
  }
  return 0;
}

void remove_checksum( unsigned int array[], std::size_t capacity ){
  for (int a=0;a<capacity;a++){
    array[a] = remove_checksum(array[a]);
  }
}


#ifndef MARMOSET_TESTING

int main() {

  unsigned int value_to_protect{12345678};
  
  unsigned int protected_value = add_checksum(value_to_protect);
  std::cout << "The value " << value_to_protect
  << " with the checksum added is " << protected_value
  << "." << std::endl;

  if (verify_checksum(protected_value))
    {
    std::cout << "The checksum is valid." << std::endl;
    
    }
  else {
    std::cout << "The checksum is invalid." << std::endl;
    }

  const std::size_t QTY_VALUES {3};
  unsigned int value_series[QTY_VALUES] {20201122, 20209913, 20224012};
 
  add_checksum(value_series, QTY_VALUES);
  std::cout << "\nSeries with checksums added: ";
  for (std::size_t series_index {0};
    series_index < QTY_VALUES; series_index++)
    {
    std::cout << value_series[series_index] << " " << std::endl;
    }

  if (verify_checksum(202011227))
    {
    std::cout << "The checksum is valid." << std::endl;
    
    }
  else {
    std::cout << "The checksum is invalid." << std::endl;
    }

  int removed = remove_checksum(protected_value);
  std::cout << "The checksum removed is " << removed
  << "." << std::endl;

  remove_checksum(value_series, QTY_VALUES);
  std::cout << "\nSeries with checksums removed: ";
  for (std::size_t series_index {0};
    series_index < QTY_VALUES; series_index++)
    {
    std::cout << value_series[series_index] << " " << std::endl;
    }


std::cout << std::endl;
return 0;

}
#endif
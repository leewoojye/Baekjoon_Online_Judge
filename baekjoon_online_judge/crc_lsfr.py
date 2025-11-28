def crc_lfsr(data: str, divisor: str) -> str:
    
    n = len(divisor) - 1
    
    # 레지스터 초기화
    register = 0
    poly = int(divisor, 2)
    
    # 입력 데이터에 n개의 0을 추가
    augmented_data = data + "0" * n
    
    for bit in augmented_data:

        msb_is_1 = (register & (1 << (n - 1))) != 0
        
        # 레지스터를 왼쪽으로 1칸 시프트하고, 들어오는 비트를 맨 뒤(LSB)에 삽입
        register = ((register << 1) & ((1 << n) - 1)) | int(bit)
        
        # 이전에 MSB가 1이었다면 Poly와 XOR 수행
        if msb_is_1:
            register = register ^ (poly & ((1 << n) - 1))

    crc = format(register, f'0{n}b')
    return crc

def main():
    data = input("Data (binary): ")
    divisor = input("Divisor (binary): ")
    crc = crc_lfsr(data, divisor)
    print(f"CRC remainder: {crc}")
    # 송신 데이터
    sent_data = data + crc
    print(f"Sent data: {sent_data}")
    # 수신 시 검증
    check_crc = crc_lfsr(sent_data, divisor)
    if all(b == '0' for b in check_crc):
        print("No error detected.")
    else:
        print("Error detected.")
if __name__ == "__main__":
    main()
def crc_division(data: str, divisor: str) -> str:
    
    n = len(divisor) - 1
    # redundant bit 0 추가
    # 어떤 수 A가 B로 나누어떨어지면(나머지가 0이면), A 뒤에 0을 몇 개 더 붙여도(자릿수를 늘려도) 여전히 B로 나누어떨어지는 성질을 활용,
    # 송신, 수신측 모든 호출에서 0을 덧붙임
    temp_data = list(data + "0" * n)
    divisor_list = list(divisor)

    # division 수행
    for i in range(len(data)):
        # 맨 앞자리가 1인 경우에만 XOR 연산 수행
        if temp_data[i] == '1':
            for j in range(len(divisor)):
                if temp_data[i + j] == divisor_list[j]:
                    temp_data[i + j] = '0'
                else:
                    temp_data[i + j] = '1'

    remainder = "".join(temp_data)[-n:]
    
    return remainder

def main():
    data = input("Data (binary): ")
    divisor = input("Divisor (binary): ")
    # 송신 측 CRC 계산
    crc = crc_division(data, divisor)
    print(f"CRC remainder: {crc}")
    # 송신 데이터
    sent_data = data + crc
    print(f"Sent data: {sent_data}")
    # 수신 측 확인
    result_crc = crc_division(sent_data, divisor)
    if int(result_crc, 2) == 0: # 문자열을 2진수 정수로 표현
        print("No error detected.")
    else:
        print("Error detected.")
if __name__ == "__main__":
    main()
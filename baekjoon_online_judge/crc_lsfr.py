def crc_lfsr(data: str, divisor: str) -> str:
    
    # CRC 비트 수 (다항식 차수) 계산
    n = len(divisor) - 1
    
    # 레지스터 초기화 (정수형 변수 0)
    register = 0
    # 이진수 문자열인 divisor를 정수형(int)으로 변환
    poly = int(divisor, 2)
    
    # 입력 데이터 뒤에 n개의 0을 추가 (CRC 계산을 위한 증강)
    augmented_data = data + "0" * n
    
    # 증강된 데이터의 비트를 하나씩 순회
    for bit in augmented_data:
        
        # [중요] 현재 레지스터의 최상위 비트(MSB)가 1인지 확인합니다.
        # (1 << (n - 1))은 n번째 자리에 1이 있는 마스크입니다.
        # 이 비트가 1이라면, 시프트 후 오버플로우가 발생하여 XOR 연산이 필요함을 의미합니다.
        msb_is_1 = (register & (1 << (n - 1))) != 0
        
        # 레지스터를 왼쪽으로 1칸 시프트(<< 1)하고, 
        # ((1 << n) - 1) 마스크를 씌워 n비트 크기를 유지(상위 비트 삭제)한 뒤,
        # 새로운 입력 비트(int(bit))를 맨 뒤(LSB)에 채워 넣습니다(|).
        register = ((register << 1) & ((1 << n) - 1)) | int(bit)
        
        # 시프트하기 전의 MSB가 1이었다면, Poly(Divisor)와 XOR(^) 연산을 수행합니다.
        # (poly & ((1 << n) - 1))는 Divisor의 최상위 비트를 뺀 나머지 부분입니다.
        if msb_is_1:
            register = register ^ (poly & ((1 << n) - 1))

    # 최종 레지스터에 남은 값이 CRC입니다. n자리 이진수 문자열 포맷으로 변환합니다.
    crc = format(register, f'0{n}b')
    return crc
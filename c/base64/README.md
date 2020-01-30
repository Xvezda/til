# Base64 구현사항

1. Base64 문자열 테이블을 만듭니다.
    * A~Z: 26 characters
    * a~z: 26 characters
    * 0~9: 10 characters
    * +: 1 character
    * /: 1 character
    * =: padding character
2. 문자열을 이어붙여 1바이트에 8비트인 배열에서 1블록 당 6비트가 되도록 쪼갭니다.
3. 인코딩 결과물은 항상 4의 배수 바이트가 되도록 하며, 부족한 비트는 0으로 채웁니다.
4. 각 블록을 문자열 테이블에 대응 시킵니다. 위 단계에서 채운 부족한 비트(패딩)는 블록 전체 6비트가 패딩으로 채워졌을때 0에 해당하는 `A`가 아닌 padding character `=` 를 사용하도록 합니다.


## Reference
* https://blogs.oracle.com/rammenon/base64-explained

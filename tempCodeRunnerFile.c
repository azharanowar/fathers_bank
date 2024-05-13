void userLogin() {
    char givenUsername[20];
    char givenPassword[20];

    printf("Enter your username here: ");
    fgets(givenUsername, sizeof(givenUsername), stdin);

    printf("Enter your password here: ");
    fgets(givenPassword, sizeof(givenPassword), stdin);

    // Compute the SHA-256 hash of the password
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    sha256(givenPassword, hashedPassword);

    printf("Given username: %s", givenUsername);
    printf("Given password (hashed): ");
    printEncryptedPassword(hashedPassword);
}
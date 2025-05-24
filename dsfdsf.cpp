
// // Reconstruct 16-bit word (little-endian: LSB first)
//     uint16_t word2 = static_cast<uint8_t>(const_buffer[supported_dma_start_bytes]) |
//                     (static_cast<uint8_t>(const_buffer[supported_dma_start_bytes] + 1) << 8);

//     // Print bits MSB to LSB
//     std::cout << "Bits of word: ";
//     for (int i = 15; i >= 0; --i) {
//         std::cout << ((word2 >> i) & 1);
//         if (i % 4 == 0) std::cout << ' '; // Optional: group by nibbles
//     }
//     std::cout << std::endl;
// unsigned int v = static_cast<unsigned int>(const_buffer[supported_dma_start_bytes]); // LSB contains the supported dma modes
// 	unsigned r = 0;														 // Counter for bit shifts, also lg(v).

// 	while (v)
// 	{
// 		v >>= 1;
// 		r++;
// 		std::cout << "v: " << v << ", r: " << r << std::endl;
// 	}




// Reconstruct 16-bit word (little-endian: LSB first)
    // uint16_t word = static_cast<uint8_t>(smart_buffer[0]) |
    //                 (static_cast<uint8_t>(smart_buffer[1]) << 8);

    // // Print bits MSB to LSB
    // std::cout << "Bits of word: ";
    // for (int i = 15; i >= 0; --i) {
    //     std::cout << ((word >> i) & 1);
    //     if (i % 4 == 0) std::cout << ' '; // Optional: group by nibbles
    // }
    // std::cout << std::endl;
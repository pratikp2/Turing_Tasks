import hashlib

def calculate_checksum(data: bytes) -> str:
	"""
	Calculates the SHA-256 checksum of the given data.

	Args:
		data (bytes): The data to calculate the checksum for.

	Returns:
		str: The hexadecimal digest of the SHA-256 checksum.
	"""
	checksum = hashlib.sha256(data).hexdigest()
	return checksum

if __name__ == "__main__":
	import coverage
	import unittest

	# Code to be tested
	class TestChecksumCalculation(unittest.TestCase):

		def test_calculate_checksum_empty_data(self):
			expected_checksum = 'e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855'
			self.assertEqual(calculate_checksum(b""), expected_checksum)

		def test_calculate_checksum_hello_world(self):
			data = b"Hello, world!"
			expected_checksum = 'b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9'
			self.assertEqual(calculate_checksum(data), expected_checksum)

	if __name__ == "__main__":
		cov = coverage.Coverage()
		cov.start()

		unittest.main(argv=[''], exit=False)

		cov.stop()
		cov.save()
		cov.report()
		cov.html_report()
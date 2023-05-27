# AssetImporter

The AssetImporter is a class designed for importing and packing resources into a "bin" format.

## Methods

### `AddResource(inputPath: std::filesystem::path) -> void`

The `AddResource` method allows you to add a resource for import and packing. It takes the `inputPath` file path that should be imported and packed. The resource will be read, its contents will be saved, and added to the list of resources to be packed.

### `Pack(outputPath: std::filesystem::path) -> bool`

The `Pack` method performs the packing of the added resources into a "bin" format. It takes the `outputPath` path where the output "bin" file for the packed resources will be created. The method returns `true` if the packing is successful, and `false` if there is an error.

### `ReadFile(filePath: std::filesystem::path) -> std::vector<Asset>`

The `ReadFile` method reads the packed resources from a file. It takes the `filePath` path to the "bin" file from which the packed resources will be read. The method returns a vector of `Asset` objects representing the packed resources read from the file.

### `ReadFileContents(filePath: std::filesystem::path) -> std::vector<char>`

The `ReadFileContents` method reads the contents of a file. It takes the `filePath` path to the file from which the contents will be read. The method returns a vector of `char` characters containing the data read from the file.

## Data Structure

### `Asset` Structure

The `Asset` structure represents a resource to be imported and packed. It has the following fields:

- `m_Size` (size_t): The size of the resource in bytes.
- `m_Name` (std::string): The name of the resource.
- `m_Data` (std::vector<char>): The data of the resource.
- `m_Type` (AssetType): The type of the resource.

## Example Usage

# Export assets
```AssetImporter --export -add=resource1.txt -add=resource2.png -add=resource3.wav -path=output/```
    
# Import assets
```AssetImporter --import -file=packed.bin -path=output/```



using Microsoft.WindowsAzure.ServiceRuntime;
using Microsoft.WindowsAzure.Storage;
using Microsoft.WindowsAzure.Storage.Blob;
using System.Diagnostics;

namespace WebRole1 {
    public class BlobStorageService {
        //Create a blob container to store things in
        public CloudBlobContainer GetCloudBlobContainer() {
            CloudStorageAccount storageAccount = CloudStorageAccount.Parse
               (RoleEnvironment.GetConfigurationSettingValue("StorageConnectionString"));

            CloudBlobClient blobClient = storageAccount.CreateCloudBlobClient();

            CloudBlobContainer blobContainer = blobClient.GetContainerReference("qtpic");
            if (blobContainer.CreateIfNotExists()) {
                blobContainer.SetPermissions(
                    new BlobContainerPermissions {
                        PublicAccess = BlobContainerPublicAccessType.Blob
                    });
            }
            return blobContainer;
        }
    }
}
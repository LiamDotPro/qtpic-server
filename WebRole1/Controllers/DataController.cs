using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Data.Entity.Infrastructure;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using System.Web.Http.Description;
using LibQtpic.Models;
using Microsoft.WindowsAzure.Storage.Blob;
using System.IO;
using System.Web;

namespace WebRole1.Controllers
{
    public class DataController : ApiController
    {
        private PicturesContext db = new PicturesContext();
        private static CloudBlobContainer blobStorage;

        private BlobStorageService _blobStorageService = new BlobStorageService();

        private CloudBlobContainer GetBlobContainer() {
            return _blobStorageService.GetCloudBlobContainer();
        }

        //TODO: This, maybe, it might not be needed though.
        // GET: api/Data/5
        /*[ResponseType(typeof(Picture))]
        public IHttpActionResult GetPicture(int id)
        {
            Picture picture = db.Pictures.Find(id);
            if (picture == null)
            {
                return NotFound();
            }

            CloudBlockBlob blob = GetBlobContainer().GetBlockBlobReference(picture.BlobPath);
            Stream blobStream = blob.OpenRead();

            IHttpActionResult res;
            HttpResponseMessage msg = new HttpResponseMessage(HttpStatusCode.OK);
            msg.Content = new StreamContent(blobStream);
            msg.Content.Headers.ContentLength = blob.Properties.Length;
            msg.Content.Headers.ContentType = new System.Net.Http.Headers.MediaTypeHeaderValue("image/*");
            msg.Content.Headers.ContentDisposition = new System.Net.Http.Headers.ContentDispositionHeaderValue("attachment") {
                FileName = picture.FileName,
                Size = blob.Properties.Length
            };

            res = ResponseMessage(msg);

            return res;
        }*/

        // PUT: api/Data/5
        /*[ResponseType(typeof(void))]
        public IHttpActionResult PutPicture(int id)
        {
            try {
                var request = HttpContext.Current.Request;

                Picture p = db.Pictures.Find(id);
                if (p == null)
                    return NotFound();

                if (p.BlobPath != null)
                    return BadRequest();

                var blobTarget = "username/" + p.FileName;

                var blob = GetBlobContainer().GetBlockBlobReference(blobTarget);
                blob.Properties.ContentType = "image/*";
                blob.UploadFromStream(request.InputStream);

                p.BlobPath = blobTarget;
                db.Entry(p).State = EntityState.Modified;
                db.SaveChanges();

                return Ok();

            } catch (Exception e) {
                Console.WriteLine(e.Message);
                return BadRequest();
            }   
        }*/

        // POST: api/Data
        [ResponseType(typeof(void))]
        public IHttpActionResult PostPicture() {
            try {
                System.Diagnostics.Trace.WriteLine(string.Format("WebRole: Saving image."));
                DateTime now = DateTime.Now;
                var request = HttpContext.Current.Request;

                Picture picture = new Picture() {
                    FileName = string.Format("qtpic-{0}.png", now.ToString("yyyy-MM-dd-HH-mm-ss")),
                    UploadTime = now
                };

                var blobTarget = "username/" + picture.FileName;

                var blob = GetBlobContainer().GetBlockBlobReference(blobTarget);
                blob.Properties.ContentType = "image/png";
                blob.UploadFromStream(request.InputStream);

                picture.BlobPath = blobTarget;

                db.Pictures.Add(picture);
                db.SaveChanges();

                return Ok();

            } catch (Exception e) {
                Console.WriteLine(e.Message);
                return BadRequest();
            }
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                db.Dispose();
            }
            base.Dispose(disposing);
        }

        private bool PictureExists(int id)
        {
            return db.Pictures.Count(e => e.picId == id) > 0;
        }
    }
}
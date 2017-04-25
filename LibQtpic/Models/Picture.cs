using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibQtpic.Models {
    public class Picture {

        [Key]
        public int picId { get; set; }

        [StringLength(40)]
        public string FileName { get; set; }

        [StringLength(1024)]
        public string BlobPath { get; set; }
        
        public DateTime UploadTime { get; set; }
    }
}

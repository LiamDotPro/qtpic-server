using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace LibQtpic.Models {
    public class PicturesContext : DbContext {
        public PicturesContext() : base("PicturesContext") {

        }

        public PicturesContext(string connString) : base(connString) {

        }

        public DbSet<Picture> Pictures { get; set; }
    }
}

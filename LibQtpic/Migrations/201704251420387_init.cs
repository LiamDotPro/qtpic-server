namespace LibQtpic.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class init : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Pictures",
                c => new
                    {
                        picId = c.Int(nullable: false, identity: true),
                        FileName = c.String(maxLength: 40),
                        BlobPath = c.String(maxLength: 1024),
                        UploadTime = c.DateTime(nullable: false),
                    })
                .PrimaryKey(t => t.picId);
            
        }
        
        public override void Down()
        {
            DropTable("dbo.Pictures");
        }
    }
}

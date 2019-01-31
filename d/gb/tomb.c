// tomb.c ÑïÖİ·ØÄ¹
#include <ansi.h>
inherit ROOM;

string look_shibei();
int do_pull(string arg);
void close_door();

void create()
{
	set("short","·ØÄ¹");
	set("long", @LONG
ÕâÊÇÒ»¸ö½¨ÔÚ¸ÚÉÏ×î¸ß´¦µÄÒ»¸ö´ó·Ø£¬µØÉÏ²åÁË¼¸ÖùÏã£¬»¹ÔÚÈ¼×Å¡£
¿´À´ÓĞÈË¾­³£À´Õâ¡£·ØÉÏÁ¢ÁËÒ»¸ö´óÊ¯±®(shibei)£¬ÅÔ±ß»¹ÓĞÒ»¸öÌú»·
(huan)¡£ÕâÀï·çºÜ´ó£¬³ıÁËÒşÒş´ÓÔ¶´¦´«À´ÕóÕó¹··ÍÉù£¬ÄãÊ²Ã´Ò²Ìı²»
µ½¡£
LONG
	);
	set("item_desc",([
	"shibei" : (: look_shibei :),
	"huan" : "ÕâÊÇÒ»¸öÌú»·£¬¿´ÉÏÈ¥Ê®·Ö¹â»¬¡£\n",
	]));
	set("exits",([
	"south" : __DIR__"shangang"
	]));
	set("coor/x",110);
  set("coor/y",60);
   set("coor/z",0);
   setup();
}

void init()
{
	add_action("do_pull", "pull");
}

string look_shibei()
{
	return
	"\n"
	"   ¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡  \n"
	"   ¡ù¡ù¡ù                  ¡ù¡ù¡ù   \n"
	"   ¡ù¡ù¡ù     ÇıÖğ÷°Â²     ¡ù¡ù¡ù   \n"
	"   ¡ù¡ù¡ù     »¹ÎÒºÓÉ½     ¡ù¡ù¡ù   \n"
	"   ¡ù¡ù¡ù                  ¡ù¡ù¡ù   \n"
        "   ¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù   \n";
}

int do_pull(string arg)
{
        object room;

	if( !arg || arg!="huan" ) return 0;
	message("vision","Ä¹±®ºöÈ»·¢³öÔşÔşµÄÉùÒô£¬ÏòÒ»²à»º»ºÒÆ¿ª£¬"
	                "ÏòÏÂÂ¶³öÒ»¸öºÚ¶´¶´µÄÈë¿Ú¡£\n", this_object() );
	set("exits/down", __DIR__"fenduo2");
	if( room = load_object(__DIR__"fenduo2") ) {
 		 room->set("exits/up", __FILE__);
		 message("vision",
 "Í·¶¥ÉÏµÄÄ¹±®ºöÈ»·¢³öÔşÔşµÄÉùÒô£¬Â¶³öÒ»¸ö¹âÁÁÁÁµÄ¶´¿Ú¡£\n",room );
	} 
	remove_call_out("close_door");
	call_out("close_door", 3);
        return 1;
}

void close_door()
{
	object room;

        if( !query("exits/down") ) return;
        message("vision","Ä¹±®ºöÈ»·¢³öÔşÔşµÄÉùÒô£¬»º»ºµØÒÆ»ØÔ­´¦£¬"
                "½«ÏòÏÂµÄ¶´¿Ú¸Ç×¡ÁË¡£\n", this_object() );
        if( room = load_object(__DIR__"fenduo2") ) {
                room->delete("exits/up");
                message("vision", "Í·¶¥ÉÏµÄÄ¹±®ºöÈ»·¢³öÔşÔşµÄÉùÒô£¬"
                        "Ç½ÉÏµÄÊ¯¿éÓÖ»º»ºµØÊÕÁË»ØÈ¥£¬½×ÌİÏûÊ§ÁË¡£\n", 
room );
        }
        delete("exits/down");
}


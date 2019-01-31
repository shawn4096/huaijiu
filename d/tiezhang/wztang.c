// Room: /u/zqb/tiezhang/wztang.c
#include <ansi.h>

inherit ROOM;
string look_bian();

void create()
{
	set("short", HIY"ÎåÖ¸ÌÃ"NOR);
	set("long", @LONG
ÕâÊÇÒ»¼äÍêÈ«ÓÃ»¨¸ÚÑÒÆö³ÉµÄ´óÌü£¬Í¸³öÕóÕó±ÆÈËµÄº®Æø¡£Õû×ù·¿ÎÝÃ»ÓÐ
´°»§£¬ÏÔµÃÒõÉ­ºÚ°µ¡£Á½ÅÔµÄÇ½±ÚÉÏ²å×ÅËÉÓÍ»ð°Ñ£¬É¢·¢³ö»è»ÆµÄ¹âÁÁ£¬¼Å¾²
µÄ´óÌüÖÐ²»Ê±ÏìÆð»ð°ÑàèÅ¾µÄÈ¼ÉÕÉù¡£´óÌüµÄÕýÖÐ°Ú·Å×Å°ïÖ÷µÄ±¦×ù£¬Á½ÅÔ·Ö
ÁÐ×ÅÊ®¼¸°ÑÒÎ×Ó£¬Ö»ÓÐÓöµ½°ïÖÐ´óÊÂÊ±£¬°ïÖ÷²Å»áÔÚÕâÀïÓë²¿ÏÂÉÌÒé¡£ÔÚÕýÃæ
µÄÇ½ÉÏ¹Ò×ÅÒ»ÃæÂÆ½ðµÄºáØÒ(bian)¡£±±ÃæÓÐÒ»ÉÈÐ¡ÃÅÍ¨ÏòºóÃæ¡£
LONG
	);

        set("item_desc", ([ 
        "bian"       :       (: look_bian :),
]));

	set("exits", ([ 
"east" : __DIR__"zoulang-1",
"southdown" : __DIR__"guangchang.c",
"west" : __DIR__"zoulang-2.c",
"north" : __DIR__"hxfang.c",
]));

    set("objects", ([ 
__DIR__"npc/mayi1" :1,
__DIR__"npc/huiyi" :2,
]));

	set("no_clean_up", 0);

	set("coor/x",-330);
  set("coor/y",-250);
   set("coor/z",10);
   setup();
	
}
int valid_leave(object me, string dir)
{
        if (me->query("family/family_name") != "ÌúÕÆ°ï" &&
            present("hong xiaotian", environment(me)) &&
            (dir =="west" || dir =="north" || dir=="east"))
           return notify_fail("ºéÏøÌìÀ¹×¡ÄãµÄÈ¥Â·£¬±§È­µÀ£º·Ç±¾°ïµÜ×Ó²»µÃÈëÄÚ¡£\n");

        return ::valid_leave(me, dir);
}

string look_bian()
{
    return
    "\n" 
         BLINK HIY"          ¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù\n"
                  "          ¡ù¡ù¡¡  ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡    ¡ù¡ù\n"
                  "          ¡ù¡ù   Îå    Ö¸    Çæ    Ìì¡  ¡ù¡ù\n"     
                  "          ¡ù¡ù  ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡    ¡ù¡ù\n"
                  "          ¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù\n"NOR;
}

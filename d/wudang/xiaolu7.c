//û// xiaolu1.c ÁÖ¼äĞ¡¾¶
#include <ansi.h>

inherit ROOM;
int do_jiao(string arg);

void create()
{
        set("short", "ÁÖ¼äĞ¡¾¶");
        set("long", @LONG
Äã×ßÔÚÒ»ÌõĞ¡¾¶ÉÏ£¬Á½ÅÔÖÖÂúÁËÖñ×Ó£¬ĞŞóòÉ­É­£¬ÂÌÒñÂúµØ£¬³ı
ÁËÖñÒ¶ÉùºÍÄñÃùÉù£¬Ìı²»µ½±ğµÄ¶¯¾²¡£±ßÉÏÓĞĞí¶àÅèÔÔ£¬ÆäÖĞÒ»Öê³¤
Éú¹ûÊ÷(guoshu)¾ÍÎªÕä¹ó¡£
LONG
        );

        set("exits", ([
                "west" : __DIR__"liangongfang",
                "southeast" : __DIR__"xilang1",
                "north" : __DIR__"xixiangfang",

        ]));
                 
        set("objects",([
                "/kungfu/class/wudang/fengsong" : 1,
        ]));


        set("item_desc", ([
               "guoshu" : "ÕâÊÇÖê´ÓÉîÉ½ÒÆÖ²µÄÏÉ¹ûÊ÷Ãç£¬ÒòÎª³¤ÓÚ·²¼ä¶øÊ§È¥ÁéÆø¡£Ö¦Ò¶Î®ÃÒ£¬²»ÄÜ¿ª»¨½á¹û!\n"
        ]) );

        set("jiao_count", 3);
set("guo_count", 1);

        setup();
}

void init()
{
        add_action("do_jiao", "jiao");

}
int do_jiao(string arg)
{       mapping fam;
        object me;
        object obguo;
        me = this_player();


        if ( !arg || arg != "guoshu" )
                return 0;

        if (!(fam = me->query("family")) || fam["family_name"] != "Îäµ±ÅÉ")
               return notify_fail("ÄãÓë±¾ÅÉËØÎŞÀ´Íù£¬ÓÖºÎ±ØÎŞÊÂÏ×ÒóÇÚ!\n");

    if (! present("xiang cha", this_player()))
        return notify_fail("ÄãÄÃÊ²Ã´À´½½?!\n");
     
     message_vision(HIG"$NÏ¸ĞÄµØ°Ñ²è±­ÀïµÄÅ®¶ùÏã½½ÔÚ³¤Éú¹ûÊ÷ÉÏ¡£\n"NOR, me);
     if (present("xiang cha", me))
     destruct(present("xiang cha",me));

     add("jiao_count", -1);
     if (query("jiao_count") > 0) {
        message_vision(HIG"Ïã²è±»¹ûÊ÷ÎüÊÕ£¬Ö¦Ò¶³¤µÃ¸ü´äÂÌÁË¡£\n"NOR, me);
        return 1;
        }
     if (query("guo_count") >=1)
      {
        add("guo_count", -1);
        write(HIM"Í»È»¹ûÊ÷ÖĞ¼ä³¤³öÒ»¸ö»¨ÀÙ£¬Ëæ¼´¿ª»¨£¬ÂíÉÏ¾Í½á³ÉÒ»¸öÁîÈËÍÙÑÊÓûµÎµÄ³¤Éú¹û!\n"NOR);
        message_vision("$NĞ¡ĞÄÒíÒíµØÕªÏÂ³¤Éú¹û£¬ÂúÁ³¸ßĞËµØ´§Èë»³ÖĞ¡£\n",me);
        obguo = new("/clone/medicine/rsg");
        obguo->move(me);
        set("jiao_count", 3);
        return 1;
      }
      else
      {
       set("jiao_count", 3);
       message_vision(HIG"ÓÉÓÚÓªÑø²»Á¼£¬³¤Éú¹ûÊ÷Ö»ÄÜ¿ª³öÒ»¶äÃÀÀöµÄĞ¡»¨¡£\n"NOR, me);
      }
        return 1;
}


// cangjingge.c �ؾ���
// by ahunter and shang  97/6
inherit ROOM;

string* books = ({
        "laozi1",
        "daodejing-i",
        "laozi2",
        "daodejing-i",
        "laozi8",
        "daodejing-i",
        "laozi13",
        "laozi1",
        "laozi16",
        "daodejing-i",
        "laozi18"
});

void create()
{
        set("short", "�ؾ���");
        set("long", @LONG
�����ǲؾ��󣬿�ǽ��һ����ܣ������˵��̵ĵ伮��������һ������
�εĴ����ӣ�����Ҳ�������顣һ����ͯ���������鼮��
LONG
        );

        set("exits", ([
                "northdown" : __DIR__"xilang1",
        ]));

        set("objects", ([
                __DIR__"npc/daotong" : 1,
                __DIR__"obj/"+books[random(sizeof(books))] : 1,
                __DIR__"obj/"+books[random(sizeof(books))] : 1
        ]));

        set("coor/x",-30);
  set("coor/y",-90);
   set("coor/z",110);
   setup();
}

int valid_leave(object me, string dir)
{
        object ob;

        if ( present("daode jing", me)
        ||   objectp(ob = present("corpse", me)) && present("daode jing", ob))

        {
                if (dir == "southdown" )
                {
                        return notify_fail("���¾�����Я����� !\n");
		      }
	      }
        return ::valid_leave(me, dir);
      }

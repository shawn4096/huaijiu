// cangjingge.c 藏经阁
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
        set("short", "藏经阁");
        set("long", @LONG
这里是藏经阁，靠墙是一排书架，摆满了道教的典籍。中央有一个长方
形的大桌子，上面也堆满了书。一个道童正在整理书籍。
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
                        return notify_fail("道德经不得携带外出 !\n");
		      }
	      }
        return ::valid_leave(me, dir);
      }

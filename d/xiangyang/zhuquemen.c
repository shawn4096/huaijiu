// /d/xiangyang/zhuquemen.c

inherit ROOM;

string look_gaoshi();

void create()
{
        set("short", "��ȸ��");
        set("long", @LONG
�����Ǿ������������ǵ����ţ���Ϊ�����ս����Զ�������Ե÷�������
�öࡣ���ϳ��ǿ���ȥ���ϡ����ŵ�ǽ��������һֽ��ʾ(gaoshi)��
LONG
        );
        set("outdoors", "����");

        set("item_desc", ([
                "gaoshi" : (:look_gaoshi:),
        ]));

        set("exits", ([
                "north" : __DIR__"cross2",
                "south" : __DIR__"outsroad1",
        ]));

             set("objects",([
               "/d/xiangyang/npc/guofu" : 1,
               "/d/xiangyang/npc/yelv" : 1,
        ]));

   set("coor/x",0);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",0);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",0);
  set("coor/y",-10);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n��������ʹ\n���ĵ�\n";
}


int valid_leave(object me, string dir)
{
        if (dir == "north" || dir == "south")
        if ((me->query("family/family_name")!="������")&&(me->query_temp("xy/job"))&&(present("wushi", this_object())))
                      return notify_fail("�ú��سǣ������ܡ�\n");
      return ::valid_leave(me, dir);
}



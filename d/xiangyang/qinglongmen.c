// /d/xiangyang/qinglongmen.c

inherit ROOM;

string look_gaoshi();

void create()
{
        set("short", "������");
        set("long", @LONG
�����Ǿ������������ǵĶ��ţ���ʱ���ж�����׵�ʿ��������ȥ����
���߿��Խ��밲�ա����վ��ڡ����ŵ�ǽ��������һֽ��ʾ(gaoshi)��
LONG
        );
        set("outdoors", "����");

        set("item_desc", ([
                "gaoshi" : (:look_gaoshi:),
        ]));

        set("exits", ([
                "east" : "/d/xiangyang/outeroad1",
                "west" : "/d/xiangyang/eroad1",
        ]));

        set("objects", ([
                "/d/xiangyang/npc/chengying" : 1,
                "/d/xiangyang/npc/wu" : 1,
                "/d/xiangyang/npc/feng" : 1,
        ]));

        set("coor/x",20);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",20);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",20);
  set("coor/y",0);
   set("coor/z",0);
   setup();}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n��������ʹ\n���ĵ�\n";
}

int valid_leave(object me, string dir)
{
        if (dir == "west" || dir == "east")
        if ((me->query("family/family_name")!="������")&&(me->query_temp("xy/job"))&&(present("bing", this_object())))
                      return notify_fail("�ú��سǣ������ܡ�\n");
      return ::valid_leave(me, dir);
}


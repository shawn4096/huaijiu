// jinku.c
// this is made by leontt
// update 2000.10.04

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
         set("short",HIG"����"NOR);
         set("long",
  "������Ľ�ݲ�Ĺ�ڵ�һ�����ҡ����Ϸ��˼�����������Ĵ�����(box)��\n"
"ǽ�Ϲ����˴���������ʵ۵Ļ��������а���һ������(chair)��\n"
);
         set("exits",([
             "south" : __DIR__"fenmu",
]));
        set("item_desc", ([
             "chair" : "�����������ҷ����ϸ���һ���񹤾�ϸ����ͷ(tou)��\n", 
               "box": "����һ����̾�������ɫ����Ĵ����ӣ�����϶��в��ٱ��\n",
]));
                setup(); 
}

int init()
{
        add_action("do_sit","sit");  
        add_action("do_zhuan","zhuan");  
        add_action("do_open","open");
}

int do_sit(string arg)
{

        if ( !arg || (arg != "chair") )
                return notify_fail("��Ҫ��ʲô���棿\n");       
        
        if (this_player()->query("family/family_name") != "����Ľ��")
                return notify_fail("�㲻�ǹ���Ľ�ݼҵ��ˣ��������㲻�����߳�ô����\n");
        if (this_player()->query_temp("mark/sit"))
                return notify_fail("���Ѿ������ˡ�\n");   
                        
        this_player()->set_temp("mark/sit", 1);
        return notify_fail("�����һ������ҡ��ڵ������������ϡ�\n");     
}

int do_zhuan(string arg)
{
 	if ( !arg || ((arg != "left tou") && (arg != "right tou")) )
                return notify_fail("��Ҫתʲô��\n");       
       
        if (this_player()->query("family/family_name") != "����Ľ��")
                return notify_fail("��Ҫ��ʲô ����\n");

        if (!this_player()->query_temp("mark/sit"))
                return notify_fail("��Ҫ��ʲô ����\n");

        if ((int)this_player()->query("neili") < 10000 )
                return notify_fail("��׷��˰��쾢�����ʲôҲûת����\n");

          if (arg == "left tou")
        {
                this_player()->add_temp("left/tou",1);
                tell_object(this_player(),"�����ߵ���ͷת��һȦ��\n");
        }

          if(arg == "right tou")
        {
                this_player()->add_temp("right/tou",1);
                tell_object(this_player(),"����ұߵ���ͷת��һȦ��\n");
        }

          if((int)this_player()->query_temp("left/tou") == 5 &&
             (int)this_player()->query_temp("right/tou") == 6)
        {
                message_vision("ֻ������ͻȻת����ǽ����ת������ʱ��$N�Ѿ������ˡ�\n",this_player());
                  this_player()->move(__DIR__"mishi1");
                message_vision("ֻ��ǽ�ڷ�ת��$N��ǽ��ת�˳�����\n",this_player());
        } 

if((int)this_player()->query_temp("left/tou") > 5 ||
           (int)this_player()->query_temp("right/tou")> 6)
        {
                this_player()->delete_temp("left/tou");
                this_player()->delete_temp("right/tou");
        }

        return 1;

}

int do_open(string arg)
{

        if ( !arg || (arg != "box") )
                return notify_fail("��Ҫ��ʲô��\n");       

         message_vision("ֻ��һ���Ҽ������$N�߶�û�ߣ����ض�����\n",this_player());
        this_player()->set_temp("last_damage_from", "��ײ���ر��Ҽ���");
        this_player()->die();
               return 1;
}
                
       

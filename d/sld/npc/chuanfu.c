//wzfeng 98 10 13
//chuanfu.c
inherit NPC;

int ask_chuhai();
void create()
{
  set_name("����",({ "chuan fu","chuan","fu"}));
        set("long",             
                "����һ���ϴ���ר�Ÿ�����������ȥ��ԭ�Ĵ�ֻ��\n"
        );
                set("gender", "����");
        set("attitude", "friendly");
                set("no_get_from", 1);
                set("unique", 1);
        set("age", 55);
                set("per",15);
        set("shen", 0);
        set("str", 30);
        set("int", 25);
        set("con", 27);
        set("dex", 29);
        set("max_qi", 500); 
        set("max_jing", 300);
        set("neili", 500);
        set("max_neili", 500);
        set("jingli", 200);
        set("eff_jingli", 200);
        set("jiali", 10);
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        
        set("combat_exp", 50000);
        create_family("������",3, "����");
        set("inquiry", ([
        "chuhai" : (: ask_chuhai :),
       "����" : (: ask_chuhai :),
        ]));
        
        setup();

}

void init()
{
    ::init();
    if(!objectp(find_object("/d/sld/md1")))
    {
        load_object("/d/sld/md1");   
    }
}

int ask_chuhai()
{
    command("say �������������ͨ�������Ҳ��ܷ��ɴ�ֻ,��Ȼ�κ��˲��������뵺������");
        return 1;
}

int accept_object(object who, object ob)
{
        if( ((string)ob->query("id") != "ling pai") || (ob->query("sld")!=1))
                return 0;
        this_player()->set("start_busy",2);
    remove_call_out("go_chuan");
    call_out("go_chuan", 2,this_player());               

/*      command("say ��Ȼ��������ͨ�����ƣ�����ʹ����ϴ���");
        message_vision("ֻ��$N���ϴ��˸����ƣ��ƺ���ʲô���š�",this_object());
        message_vision("��һ�����һ��С�����Ӻ��ϻ���ʻ����",this_object());
        message_vision("$N��˵�������Ϸ��һ��С�ģ�",this_object());
        this_player()->move(__DIR__"fanchuan");
  */
    call_out("destructing", 1, ob); 
    return 1;
        
        
}

void destructing(object ob)
{
	destruct(ob);
}

void go_chuan(object me)
{
    object fchuan;
    int i;
    string* fcname=({ __DIR__"obj/fc1",__DIR__"obj/fc2",__DIR__"obj/fc3" });

    for(i=0;i<sizeof(fcname);i++)
    {
    	if(!objectp(fchuan=find_object(fcname[i])))
        	fchuan=load_object(fcname[i]);
    	if(fchuan->query_temp("curstatus",1)!="run")
		break;
    }
    if(i>=sizeof(fcname))
    {
        command("say ����û�������һ��ɡ�\n");
        remove_call_out("go_chuan");
        call_out("go_chuan", 2,me); 
        return;
    }          
    command("say ��Ȼ��������ͨ�����ƣ�����ʹ����ϴ���\n");
    if(fchuan->query_temp("curstatus",1)=="ready")
    {
    	message_vision("ֻ��$N���ϴ��˸����ƣ��ƺ���ʲô���š�\n",this_object());
    	message_vision("��һ�����һ��С�����Ӻ��ϻ���ʻ����\n",this_object());
    	message_vision("$N��˵�������Ϸ��һ��С�ģ�\n",this_object());
	fchuan->set_temp("curstatus","ready2");
    }
    message_vision("$N����һԾ������С����\n",me);
    me->move(fcname[i]);
    tell_room(environment(me), me->name() + "Ծ�ϴ�����\n");
}
       

//wzfeng 98 10 13
//chuanfu.c
inherit NPC;

int ask_chuhai();
void create()
{
  set_name("船夫",({ "chuan fu","chuan","fu"}));
        set("long",             
                "他是一名老船夫，专门负责发派神龙岛去中原的船只。\n"
        );
                set("gender", "男性");
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
        create_family("神龙教",3, "弟子");
        set("inquiry", ([
        "chuhai" : (: ask_chuhai :),
       "出海" : (: ask_chuhai :),
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
    command("say 岛主有令，必须有通行令牌我才能发派船只,不然任何人不得擅自离岛！！！");
        return 1;
}

int accept_object(object who, object ob)
{
        if( ((string)ob->query("id") != "ling pai") || (ob->query("sld")!=1))
                return 0;
        this_player()->set("start_busy",2);
    remove_call_out("go_chuan");
    call_out("go_chuan", 2,this_player());               

/*      command("say 既然有神龙教通行令牌，我这就带你上船！");
        message_vision("只见$N向海上打了个手势，似乎是什么暗号。",this_object());
        message_vision("不一会儿，一艘小帆船从海上缓缓驶来。",this_object());
        message_vision("$N对说到，海上风大，一切小心！",this_object());
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
        command("say 现在没船，请等一会吧。\n");
        remove_call_out("go_chuan");
        call_out("go_chuan", 2,me); 
        return;
    }          
    command("say 既然有神龙教通行令牌，我这就带你上船！\n");
    if(fchuan->query_temp("curstatus",1)=="ready")
    {
    	message_vision("只见$N向海上打了个手势，似乎是什么暗号。\n",this_object());
    	message_vision("不一会儿，一艘小帆船从海上缓缓驶来。\n",this_object());
    	message_vision("$N对说到，海上风大，一切小心！\n",this_object());
	fchuan->set_temp("curstatus","ready2");
    }
    message_vision("$N轻轻一跃，上了小船。\n",me);
    me->move(fcname[i]);
    tell_room(environment(me), me->name() + "跃上船来。\n");
}
       

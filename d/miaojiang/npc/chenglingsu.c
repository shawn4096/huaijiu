// chenglingsu

inherit NPC;
 
string ask_me();
void create()
{
       set_name("������", ({ "cheng lingsu", "cheng" }));
       set("nickname", "ҩʦ");
       set("long", 
               "������ҩʦ�����ء�\n"
               "����ѽ��ж�ʮ���꣬���Ǹ���ҩ��Ϊ��ͨ��\n");
        set("gender", "Ů��");
       set("age", 21);
       set("attitude", "friendly");
       set("shen", -3000);
       set("str", 29);
       set("int", 27);
       set("con", 26);
       set("dex", 26);
       
       set("max_qi", 200);
       set("max_jing", 100);
       set("neili", 1000);
       set("max_neili", 1000);
       set("jiali", 10);
       set("combat_exp", 80000);
 
       set_skill("force", 60);
        set_skill("yinyun-ziqi", 60);
       set_skill("dodge", 60);
       set_skill("jinshe-zhangfa", 60);
       set_skill("tiyunzong", 60);
       set_skill("strike", 60);
       set_skill("jinshe-jianfa", 60);
       set_skill("parry", 60);
       set_skill("sword", 60);
       set_skill("poison", 160);
       set_skill("medicine", 160);
       set_skill("literate", 120);
        map_skill("force", "yinyun-ziqi");
       map_skill("dodge", "tiyunzong");
       map_skill("strike", "jinshe-zhangfa");
       map_skill("parry", "jinshe-jianfa");
       map_skill("sword", "jinshe-jianfa");
       prepare_skill("strike", "jinshe-zhangfa");

       set("inquiry", ([
              
                "�嶾��" : (: ask_me :),
                "����" : (: ask_me :),
       ]));
       setup();
       carry_object("/clone/armor/cloth")->wear();
}
void init()
{        
     add_action("do_yes","yes");
     add_action("do_no","no");
}
string ask_me()
{
       object applicant;
       object ob;
       int exp;
       applicant=this_player();

        exp=(int)applicant->query("combat_exp",1); 
        if(exp<90000)
        return "�����㹦�򣬿������嶾�̵�ɽҲ�ϲ�ȥ���ȼ�����˵�ɣ�\n"; 
 
        if (  present("jiuxuebiyun dan", this_player()) )
        return "���Ѿ��������ˣ�Ϊ�λ�Ҫ����Ҫ����ҩ�������ƣ���Ҫ̫̰�ģ�\n";
       
        if( applicant->query("wudu_jiedu") ){
        ob = new(__DIR__"obj/jxdan1");
        ob->move(applicant);
        message_vision("$N���һ�ž�ѩ���Ƶ���\n",this_player());
 
        return "���ϴδ�Ӧ�ҵ����黹û������������Ҫ�� ������������ü��
�����˵��������������һ�ţ���Ҫ����ȥ�ɡ�\n";
        }
 
         applicant->set_temp("marks/��",1);
         return "�嶾�̵Ľ��������˸����滨��ݣ����д󲿷־��о޶������һ������
�����������У��ؽ��ж��������������ȥ�嶾�̣��������пŵ�ҩ�ɵ����䶾��������
��ȥ����Ѱ��ѩ�룬��Ը����ҩ�����㣬�㿼��һ�£��Ƿ��Ӧ(yes)���߲���Ӧ(no)�ҡ�\n";
        
        
}
int do_yes()
{
    
   object jxdan, me, ob;
   me = this_object();
   ob = this_player();

   if(!ob->query_temp("marks/��")) return 0;
        jxdan = new(__DIR__"obj/jxdan");
   ob->set("wudu_jiedu", 1);
   ob->delete_temp("marks/��");	
   jxdan->move(this_player());
   message_vision("$N���һ�ž�ѩ���Ƶ���\n",this_player());
   message_vision("$N����΢΢һЦ��˵����ף�����˳��������ϣ�������Զ����š�\n",me, this_object()); 
   return 1;
} 
int do_no()
{
   object me = this_player();
   if(!me->query_temp("marks/��")) return 0;
   message_vision("���������ε�һЦ��˵������Ȼ�㲻�ܴ�Ӧ�ҵ�Ҫ�󣬵�ҩ��Ȼ���ܸ��㡣\n",me);
   me->delete_temp("marks/��");	
   
   return 1;
}
int accept_object(object who, object ob,object me)
{
        if (ob->query("id") != "xue zhu" ){
             command("? "+(string)who->query("id"));
             return 0;
             }
       
        command("thank " + who->query("id"));
        command("say ���Ȼ�Զ����ţ��´���Ҫ��ȥ�嶾�������Ұɡ�\n");
        call_out("destroying", 1, ob);        
        who->delete("wudu_jiedu");
        return 1;
}
void destroying(object obj)
{
        destruct(obj);
        return;
}

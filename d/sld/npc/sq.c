// ����

inherit NPC;

int ask_zhushao();
void destructing(object ob);
string ask_houshan();
string ask_me();
void create()
{
        set_name("����", ({ "su quan","su" }));
        set("long", "����ģ��������ʮ�����꣬��һ����ò�ٸ���΢΢һЦ��������̬������\n������ƥ�����������̽����ķ��ˡ�\n");
        set("gender", "Ů��");
        set("title", "�����̽�������"); 
        set("age", 23);       
        set("str", 20);
        set("int", 22);
        set("con", 22);
        set("dex", 22);
        set("per", 30);
        set("combat_exp", 400000);
        set("shen", -1000);
        set("attitude", "peaceful");
        set("max_qi",2000);
        set("max_jing",2000);
        set("neili",1800);
        set("max_neili",1800);
        set("jingli",1800);
        set("eff_jingli",1800);
        set("jiali",40);
        set("score", 15000);
        set("yaoli_count",1);
      
      //set_skill("unarmed", 150);
      //set_skill("move",150);
        set_skill("force", 100);
        set_skill("dodge", 100);
      set_skill("parry",100);
        set_skill("strike",100);
      set_skill("huagu-mianzhang", 100);
      set_skill("youlong-shenfa",100);
      set_skill("dulong-dafa",100);
      
        map_skill("force", "dulong-dafa");
        map_skill("dodge", "youlong-shenfa");
        //map_skill("move", "youlong-shengfa");
       map_skill("strike", "huagu-mianzhang");
      //map_skill("unarmed","huagu-mianzhang");
      map_skill("parry","huagu-mianzhang");
      
      set("inquiry", ([
                "����" : (: ask_zhushao :),
                "zhushao" : (: ask_zhushao :),
                   "�ɸ���": (: ask_houshan() :),
                "����ҩ��" : (: ask_me :),       
         ]) );
      set("chat_chance", 10);
      set("chat_msg", ({
            "�������������������ذ����Ȼ�������Ͼ���������������\n",
      }));
      create_family("������",1, "��������");
      setup();
      carry_object(__DIR__"obj/skirt")->wear();     
}

int accept_object(object me, object ob)
{
        object obj;

        if( ob->query("weapon_prop/damage") >= 80){
            obj=unew(BINGQI_D("xtbs"));
          if(obj){
            obj->move(me);
            tell_object(me,"����������ģ�����̫���ˣ��������ذ�׾��͸���ɣ�\n");
            tell_room(environment(me), "������" + me->name() + "һ������ذ�ס�\n");
          }
          else {
            tell_object(me,"����������ģ�����̫���ˣ��������������ģ�\n");
            me->add("shen", -(10000+random(10001)));
          }
          ob->move("/d/sld/md1");
          call_out("destructing", 0, ob); 
          return 1;
        }
        return 0;
}

void destructing(object ob)
{
        if(ob)
        destruct(ob);
}

int ask_zhushao()
{
       object me,ob,zs;
       mapping myfam;
       object* inv;
       int i;

       me=this_player();
       ob=this_object();
       myfam = (mapping)me->query("family");
       if(!myfam || myfam["family_name"] != "������"){
          return 0;
       }
       if(me->query("combat_exp", 1) < 500000){
          command("say �����ڿɲ��ܸ�������Ŷ��");
          return 1;
       }
       inv = all_inventory(me);
       for(i=0; i<sizeof(inv); i++)       
       if(inv[i]->query("id")=="zhushao")
           break;
       if(i>=sizeof(inv)){
         zs= new(__DIR__"obj/zhushao");
         if (!zs)  return notify_fail("�쳣����\n");
//       ob->set("owner",me);
         tell_object(me,"�ðɣ��Ҹ�������ڣ��ɲ�ҪŪ���ˡ�\n");
         tell_room(environment(me), "������" + me->name() + "һ�����ڡ�\n");
         zs->move(me);      
       }
       else {
         tell_object(me,"�㲻���Ѿ���������ô��\n");
       }
       return 1;
}

string ask_me()
{
 object ob;
 mapping fam;
 if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
 return RANK_D->query_respect(this_player()) + 
                "�뱾��������������֪�˻��Ӻ�̸��";
       if (query("yaoli_count") < 1)  
           return "�������ˣ��Ǳ������Ѿ��������ˡ�\n";
       ob=new("/clone/book/slyaoli-book.c");
       ob->move(this_player());
       add("yaoli_count", -1);
       message_vision("�����ӻ����ͳ�һ������ҩ���ݸ�$N��\n",this_player());
       return "�Ȿ�����Һ�½�������������ģ�����ȥ��Ҫ�ú��о�����";
      }        

string ask_houshan()
{
    object me=this_player();
    int lvl = (int)me->query_skill("shenlong-yaoli", 1);     
    if ( lvl < 120 ) return "�ɸ�����������ңʤ��,�㻹�����ʸ�ȥ��";
    tell_object(me, "��Ȼ���ʵ��ˣ����Ҿʹ���ȥ�ɡ�\n");
    me->move("/d/sld/xfj");
    return "��һ�������ӡ�";
}


int ask_hu_quest()
{
    object me = this_player();
    if (me->query_temp("hu/quest1")!=2) {
        command("say ��ôͻȻ��������ʲô��");
        return 1; } else {
        command("say ԭ�������������ڣ�");
        command("jump");
        command("say �Ұ�������ݺݵ���������һ�һ�٣�������Ҳ�Լ������Լ��Ķ����ˡ�");
        command("say ���������������Կ�������ػ�ܸ��ˡ�");
        me->set_temp("hu/quest1",3);
        return 1;}
}

int ask_hu()
{
    object me = this_player();
    if (!me->query_temp("hu/quest2")) {
        command("say ����ţ�����ųƵ���ҽ�ɣ�ҽ��һ��������Ƣ���е�֡�");
        return 1; } else {
        command("ah");
        command("say ���ǶԲ�ס��������̽�Ҫ���£���ʵ�ڳ鲻����");
        command("say �鷳�����������˰�æ�������Ϳ��š�");
        command("say ����������޼ɰ��ã���������С�����ӡ�");
        command("say �������������ȥ���ú����������ɡ�");
        me->apply_condition("hu_quest",5);
        new("/d/mingjiao/obj/tieyan")->move(me);
        return 1;}
}

int ask_hdg()
{
        object me = this_player();
        command("say �������Ǻ���ţ��ҽ�ľ�����");
        command("say ���ڳ����ϰ����������ź��������ҵ��ˡ�");
        me->set_temp("hdg",1);
        return 1;
}

string ask_qishang()
{
        mapping fam; 
        object me=this_player();
        fam = me->query("family");
        if (!fam || fam["family_name"] != "����" || fam["master_name"] != "���޼�")
                return "��....���ҿɲ��������������ʱ��˰ɡ�";
        if(me->query_skill("qishang-quan", 1) <50)
                return "���Ȱ�����ȭ�Ļ��������˵�ɡ�\n";
        if(me->query("xie_qishang"))
                return "�ף��常�����Ѿ�������ȭ��ȭ���������\n";
        if(me->query_temp("marks/����"))
                return "�ף��Ҳ��ǽ������ȥ�ݷ����常лʨ������\n";
        me->set("luopan/bhd");
        me->set_temp("marks/����",1);
        command("hmm");
        command("whisper "+me->query("id")+" ���常�ڼ��������ϣ����λ�ڻƵ����Ա��Ű���ʮ���Զ����ٸ�����ĵط���");
        new("/d/mingjiao/obj/luopan")->move(this_object());
        command("give luo pan to "+me->query("id"));
        return "������ȭ���ǵ������常���Դ��ҵľ�����������������ĺ��������ͳ���ȥ�ݷ����常�ɣ�\n";
}

string ask_book()
{
        mapping fam; 
        object me=this_player();
        fam = me->query("family");
        if (!fam || fam["family_name"] != "����" || fam["master_name"] != "���޼�")
                return "����һ��̫��ȭ�����ǵ������䵱��̫ʦ���͸��ҵġ�";
        me->set_temp("marks/��1",1);
        return "����һ��̫��ȭ�����ǵ������䵱��̫ʦ���͸��ҵģ����ҽ���ɢ���ˡ�";
}

string ask_me()
{
        object me=this_player();
        if(me->query("jiuyang/zhang"))
            return "��֪�����������С��˻��ĺ�����ô��";
        if(!me->query("jiuyang/wei"))
            return "������̷��ٲ�ʢ��Ҳδ������ʲô�����Ϣ��";
        me->set("jiuyang/zhang", 1);
            return "�뵱��̫ʦ�������������������ɡ�������ʥ�����������������˵���������С���\n"+
                   "��֪���˻��кκ��塣";
}

string ask_shu()
{
        mapping fam; 
        object ob;
        if (!(fam = this_player()->query("family")) || fam["family_name"] != "����")
            return "��....���ҿɲ��������������ʱ��˰ɡ�";
        ob = unew("/d/mingjiao/obj/cuff_book");
        if(!clonep(ob)) return "�������ˣ�������ȭ�ס��Ѿ�����ʦ����ȥ�ˡ�";
        if(clonep(ob) && ob->violate_unique()){
           destruct(ob);
           return "�������ˣ�������ȭ�ס��Ѿ�����ʦ����ȥ�ˡ�";
        } 
        ob->move(this_player());
        return "�ðɣ��Ȿ������ȭ�ס����û�ȥ�ú����С�";
}

int do_lingwu(string arg)
{
        object me=this_player();
        object who=this_object();
        int i = me->query_skill("qiankun-danuoyi", 1);
        if( !living(who))
           return notify_fail("���޼����ڵ�״���������޷��ش����κ����⡣\n");
        if (!arg || arg !="qiankun-danuoyi" ){
           message_vision("$N��$n�ֽ�һЩ������ѧ�ϵ����ʡ�\n", me, who);
           command("dunno "+me->query("id"));
           return 1;
        }
        if (me->is_busy() || me->is_fighting()){
           command("say ����æ�Ÿɱ�������أ�æ������˵�ɡ�");
           return 1;
        }
        if( me->query("jing") < 10)
           return notify_fail("��̫���ˣ�������Ϣһ��ɡ�\n"); 
        if((int)me->query("potential", 1) < 1 ) 
           return notify_fail("��Ǳ�ܲ������Ѿ������ˡ�\n");
        if ( i <= 200 ){
           command("say ���Ǭ����Ų�Ƶȼ������������ܴ�������ѧ��ʲô��");
           return 1;
        }
        write("�������޼��ֽ̹��ڡ�" + to_chinese(arg) + "�������ʡ�\n");
        write("���������޼ɵ�ָ�㣬��"+to_chinese(arg)+"�����������һ�㡣\n");
        i = i/5*2; 
        if( i > 100 ) i = 100;
        me->receive_damage("jing", i);
        if( me->query_skill("qiankun-danuoyi", 1) < 300 )
        me->add("potential", -random(2));
        me->improve_skill(arg, me->query_skill("literate", 1)/3+1);
        return 1;
}


int accept_object(object who, object ob)
{
        object me;
        mapping fam;
        me = this_object();
        fam = who->query("family");

        if(userp(ob)) return 0; 
        if(ob->query("id") == "tie ling" && ob->query("name") == HIB"������"NOR){
         if(this_player()->query("mjling/complete")) {
            command("smile");
            command("say �һ����ú������ġ�");
            this_player()->add("mjling/ling",ob->query_amount());
            call_out("destroying", 1, ob);
            return 1; }
              command("nod");
              command("say ��л���´�����Ҫ�����������ҡ�\n");
              this_object()->add("ling",ob->query_amount());
              call_out("destroying", 1, ob);
              return 1;
        }
        if((string)ob->query("id") == "shenghuo ling"){
           if(!(fam) || fam["family_name"] != "����"){
              command("thank "+ (string)who->query("id"));
              command("say ��л��Ϊ�����һ���ʥ���֪��Ӧ����ôлл�㣿\n");
              call_out("destroying", 1, ob);
              return 1;
        }
        if(fam["family_name"] == "����" 
        &&(fam["master_name"] != "���޼�" || who->query_temp("mj_jiaozhu"))){
              command("nod "+ (string)who->query("id"));
              command("say ��Ϊ�����һ���ʥ���ʹ��Ͳ�С����\n");
              call_out("destroying", 1, ob);
              who->add("shen", who->query("combat_exp")/10+2000);
              who->add("combat_exp", 100+random(50));
              tell_object(who,HIW"�㱻������һЩ����;���ֵ��\n"NOR);
              return 1;
        }                                
        if(me->query("mj_jiaozhu")){
              command("pat "+ (string)who->query("id"));
              command("say �������������Ѿ��������ҵ��ˡ�\n");
              return 0;
        }                 
        command("ah "+(string)who->query("id"));
        command("say �㾹�һ��˱���ʥ��������ҵĵ��ӣ�");
        command("say �ϴ���������������Ѱ��ʥ���ߵ�����ϰ�����񹦣���ȥ�ص������԰ɡ�");
        who->set_temp("mj_jiaozhu", 1);
        me->set("mj_jiaozhu", 1);
        call_out("destroying", 1,  ob);
        remove_call_out("restart");
        call_out("restart", 3600, me, ob);
        return 1;
        }
        else
        if(ob->query("name") == "�������׼�" && ob->query("id") == "shouji"){
              if(ob->query("victim_user")) {
                  command("say �ⲻ����ĳ�����");
                  return 0;
              }
              if(ob->query("kill_by") != who){
                  command("say ������������ɱ�İɣ�������ô�õ������ͷ�ģ�");
                  return 0;
              }      
              command("say �ã�����ɱ�˳���Ϊлʨ�����𣬲��������������µ��ӣ�");
              command("thumb "+ (string)who->query("id"));
              call_out("destroying", 1, ob);
              who->add("shen", who->query("combat_exp")/10+2000);
              who->add("combat_exp", 100+random(50));
              who->add("potential", 40);
              if(who->query("potential") > who->query("max_pot")) 
                 who->set("potential", who->query("max_pot"));
              tell_object(who,HIW"�㱻������һЩ����Ǳ�ܺ;���ֵ��\n"NOR);
              return 1;
        }
        else return 0;
}

string ask_ling()
{
   object ob, ob1, ob2, me = this_player();
   ob1 = present("yitian jian",me);
   ob2 = present("tulong dao", me);
     if (this_object()->query("making"))
       return "��̫�ļ��ˡ�";
   if (!this_object()->query("waiting")) {
   if (!me->query_temp("mj/ling")) {
   if (!ob1 || !ob2 || me->query("family/family_name") != "����" )
       return "��������ޱȣ����ҽ̵�һ�����⸱��ʹҲ�벻������ʥ������������ġ�";
   command("consider");
   command("say ��̫ʦ��˵��������������򸾽������������һ�����������ˣ�������������������");
   command("say ��������ѱ����������ˣ�Ҳ�������ͬ���ķ�������������ʥ����ı�����");
   command("walkby");
   me->set_temp("mj/ling",1);
   return "Ҳ��....";
   } else {
   command("nod");
   command("say ���ȵ��������㳡���㡣");
   command("party ����"+me->query("name")+"Ҫ����������λ���������㳡��æ��");
   command("party Ҳ���λ֪ͨ����ʹ�����������㳡׼����");
   ob = this_object();
   ob->move("/d/mingjiao/gmd");
   ob->set("waiting",1);
   return "������һ����";
   }
   }
   if (!ob1 || !ob2)
       return "��Ĳ����أ�";
   command("ok");
   command("say ��Ȼ����׼���ã��ٵ�һ�ᣬ��Ҷ��������Ǿ������ԡ�");
   call_out("start_ling",60,me,0);
     this_object()->set("making",1);
   return "�Ϳ�׼�����ˡ�";
}

void start_ling(object me, int count)
{
   object room, *obs, ob1, ob2, ob3, ob;
   int i, neili;
   room = environment(me);
   switch (count) {
   case 0:
   if (present("wen cangsong",room) && present("yan tan",room)) {
      message_vision(HIG"��������ľ���쿪ʼ��׼���õ�ľͷ��ʯ�ѳ�һ�����\n"NOR,me);
      call_out("start_ling",20,me,1);
      } else {
      message_vision(HIG"���Ǻ�������ľ����ʹ���ڣ��޷��ɹ��Ľ���¯�\n"NOR,me); 
      me->delete_temp("mj/ling");
      this_object()->delete("making");}
   break;
   case 1:
   if (present("xin ran",room) && present("tang yang",room)) {
      message_vision(HIR"�һ������������۴�𣬺�ˮ������ΧΧ��һȦ��׼��Ӧ������״����\n"NOR,me);
      call_out("start_ling",20,me,2);
      } else {
      message_vision(HIR"�����һ𣬺�ˮ����ʹ���ڣ��޷����\n"NOR,me); 
      me->delete_temp("mj/ling");
      this_object()->delete("making");}
   break;
   case 2:
      ob1 = present("yitian jian",me);
      ob2 = present("tulong dao", me);
      ob3 = present("shenghuo ling", me);
   if (!ob1 || !ob2) {
      message_vision(HIW"����$N���˴��������޷����졣\n",me);
      me->delete_temp("mj/ling");
      this_object()->delete("making");
      return; }
   if (!ob3) {
      message_vision(HIW"����$N���˴�ʥ���û���ʺϵİ��֣��޷����졣\n",me);
      me->delete_temp("mj/ling");
      this_object()->delete("making");
      return; }
   if (present("zhuang zheng",room)) {
        message_vision(HIW"ׯ����������ѵ�������¯�У���ʼ������\n"NOR,me);
      destruct(ob1);
      destruct(ob2);
      call_out("start_ling",20,me,3);
      } else {
      message_vision(HIW"���������ʹ���ڣ��޷����졣\n"NOR,me); 
      me->delete_temp("mj/ling");
      this_object()->delete("making");}
   break;
   case 3:
      message_vision(HIY"�ڳ������̵��ӽ���ǰ��ʹ��ʥ���񹦵Ĵ����ķ���æ��\n"NOR,me);
      obs = all_inventory(room);
      for (i=0;i<sizeof(obs);i++) {
        if (obs[i]->query("family/family_name") == "����")
         neili += obs[i]->query("neili"); }
      this_object()->set("total_neili",neili);
      if (neili < 30000) {
        message_vision(HIY"���Ǵ�Ҽ��ϵ��������ǲ���ǿ�����������ľ������˹�ȥ��\n"NOR,me);
        for (i=0;i<sizeof(obs);i++) {
         if (obs[i]->query("family/family_name") == "����")
          obs[i]->unconcious(); 
          obs[i]->set("neili",0); }
        me->delete_temp("mj/ling");
        this_object()->delete("making");
      } else {
         message_vision(HIM"����������֮������������������ڿ�ʼ�������۽⣡\n"NOR,me);
         message_vision(HIM"���ѱ������ƺ���ʲôֽƬ���������̱��ճɻ��ˡ�\n"NOR,me);
         for (i=0;i<sizeof(obs);i++) {
         if (obs[i]->query("family/family_name") == "����")
          obs[i]->set("neili",0); }
         call_out("start_ling",20,me,4);
      }
   break;
   case 4:
      message_vision(HIC"�����Լ��׽�ɰ���۽����������������ȿ̺���״�����ӡ�\n"NOR,me);
      neili = this_object()->query("total_neili");
      neili = neili/10000 + random(3);
      message_vision(HIC"$N��¯����ȴ����ǰȡ����"+(neili+10)+"�������\n"NOR,this_object());
      command("party ��л��λ�İ�æ������������ɹ��ˡ�");
      command("party ���������λ��ʹ������Ϣһ�£�����Ҫ�������������ѯ�ʡ�");
      message_vision(HIW"���޼��Լ�������ʹ�뿪�˴˵ء�\n"NOR,me);
      me->delete_temp("mj/ling");
      me->set("mjling/complete",1);
      me->set("mjling/ling",10);
      ob = present("zhang wuji",room);
      ob->delete("making");
      ob->move("/d/mingjiao/sht");
      ob->set("ling",neili);
      ob = present("zhuang zheng",room);
      destruct(ob);
      ob = present("wen cangsong",room);
      destruct(ob);
      ob = present("tang yang",room);
      destruct(ob);
      ob = present("xin ran",room);
      destruct(ob);
      ob = present("yan tan",room);
      destruct(ob);
   }
}

string ask_getling()
{
   if (this_player()->query_skill("shenghuo-lingfa",1) < 150)
       return "�㹦�򻹲����ء�";
   if (present("xuantie ling", this_player()) && present("xuantie ling", this_player())->query_amount()>1)
       return "�����ϵ����Ѿ�������";
   if (this_player()->query("mjling/complete") && this_player()->query("mjling/ling") > 0) {
       command("smile");
       new("clone/weapon/xuantie-ling")->move(this_player());
         this_player()->add("mjling/ling",-1);
         return "������������⣬��Ū������";
   }
   if (this_object()->query("ling")<1)
       return "���������ϲ��������";
   command("ok");
   command("say ���������ٽ����ң���������ʹ�á�");
   this_object()->add("ling",-1);
   new("/clone/weapon/xuantie-ling")->move(this_player());
   return "��Ū���˰���";
}

void restart(object me, object ob)
{     
   if(me->query("mj_jiaozhu"))
      me->delete("mj_jiaozhu");
   if (ob) destruct(ob);
}     

void destroying(object ob)
{     
	if (ob) destruct(ob);
}     

int pfm_qishang()
{
      object me,weapon;
      me = this_object();
      weapon = me->query_temp("weapon");
      if(me->is_busy()) return 0;   
      if(me->query_skill_prepared("cuff") != "qishang-quan"){
          command("bei none");
          command("enable cuff qishang-quan");
          command("bei qishang-quan");
      }
      if(objectp(weapon)) weapon->unequip(); 
        this_object()->set("jiali", 50);
        command("perform qishang");
        return 1;
}

int pfm_chan()
{
      object me,weapon, *obj, wep;
      int i;
      mapping weapon_prop;
      me = this_object();
      weapon = me->query_temp("weapon");
      obj = all_inventory(me);
      if(me->is_busy()) return 0;
        this_object()->set("jiali", 1);
      if(weapon && weapon->query("skill_type") == "sword" ){
        command("perform chan");
        return 1;
      }
      for(i=0; i<sizeof(obj); i++) 
         if(mapp(weapon_prop = obj[i]->query("weapon_prop"))
          && obj[i]->query("skill_type")=="sword")
           wep = obj[i];
      if(wep){
         if(weapon) weapon->unequip(); 
         command("wield "+wep->query("id"));
      }
      return 1;
}

int pfm_zhen()
{
      object weapon, me;
      me = this_object();
      weapon = me->query_temp("weapon");
      if(me->is_busy()) return 0;
      if(me->query_skill_prepared("cuff") != "taiji-quan"){
         command("bei none");
         command("enable cuff taiji-quan");
         command("bei taiji-quan");
      }
      if(objectp(weapon)) weapon->unequip(); 
        this_object()->set("jiali", 25);
        command("perform zhen");
        return 1;
}

int pfm_tougu()
{
      command("exert tougu");
      return 1;
}

int pfm_yi()
{
      object me, target, *obj, *enemy;
      int i, sz;
      me = this_object();
      enemy = me->query_enemy();
      if( !enemy || !arrayp(enemy) ) return 0;
        sz = sizeof(enemy);
      if( sz > 4 ) sz = 4;
      if( sz > 0 ) target = enemy[random(sz)];
        else return 0;
      if(!me->is_killing(target->query("id"))) return 0;
        obj = all_inventory(environment(me));
        i = random(sizeof(obj));
      if(!obj[i]->is_character()) return 0;
        command("perform yi "+obj[i]->query("id"));
        return 1;
}


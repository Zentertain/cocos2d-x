Dir['projects/*/Rakefile'].each {|f| load(f) }

namespace :jenkins do
  namespace :engine do
    desc 'Archive Engine into Jenkins'
    task :archive do
      sh %q{rsync -av --exclude='.git' "$WORKSPACE/." "$HUDSON_HOME/jobs/$JOB_NAME/builds/$BUILD_ID/codebase"}
    end
  end
end
